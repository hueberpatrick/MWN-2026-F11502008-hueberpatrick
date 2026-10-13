
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

#include <fstream>
#include <iostream>

using namespace ns3;

static std::ofstream csv;
static constexpr uint32_t packetCount = 100;

static void
SendTraffic(Ptr<Socket> socket,
            Ptr<UniformRandomVariable> sizes,
            Ptr<ExponentialRandomVariable> intervals,
            uint32_t index,
            double intervalMs)
{
    // Illustrative variable packet-size distribution.
    const uint32_t possibleSizes[] = {200, 600, 1200};
    uint32_t size = possibleSizes[sizes->GetInteger(0, 2)];

    socket->Send(Create<Packet>(size));

    csv << index + 1 << ","
        << Simulator::Now().GetSeconds() << ","
        << size << ","
        << intervalMs << "\n";

    if (index + 1 < packetCount)
    {
        // Exponentially distributed inter-arrival time (mean: 50 ms).
        double nextInterval = intervals->GetValue();

        Simulator::Schedule(
            Seconds(nextInterval),
            &SendTraffic,
            socket,
            sizes,
            intervals,
            index + 1,
            nextInterval * 1000.0);
    }
}

int
main(int argc, char* argv[])
{
    RngSeedManager::SetSeed(12345);
    RngSeedManager::SetRun(1);

    NodeContainer nodes;
    nodes.Create(2);

    PointToPointHelper link;
    link.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    link.SetChannelAttribute("Delay", StringValue("10ms"));

    NetDeviceContainer devices = link.Install(nodes);

    InternetStackHelper internet;
    internet.Install(nodes);

    Ipv4AddressHelper addresses;
    addresses.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer interfaces = addresses.Assign(devices);

    const uint16_t port = 9000;

    PacketSinkHelper sinkHelper(
        "ns3::UdpSocketFactory",
        InetSocketAddress(Ipv4Address::GetAny(), port));

    ApplicationContainer sinkApps = sinkHelper.Install(nodes.Get(1));
    sinkApps.Start(Seconds(0.0));
    sinkApps.Stop(Seconds(20.0));

    Ptr<Socket> sender =
        Socket::CreateSocket(nodes.Get(0), UdpSocketFactory::GetTypeId());

    sender->Bind();
    sender->Connect(InetSocketAddress(interfaces.GetAddress(1), port));

    Ptr<UniformRandomVariable> sizes =
        CreateObject<UniformRandomVariable>();

    Ptr<ExponentialRandomVariable> intervals =
        CreateObject<ExponentialRandomVariable>();

    intervals->SetAttribute("Mean", DoubleValue(0.05));

    csv.open("ntn-traffic.csv");
    csv << "packet,time_s,size_bytes,interarrival_ms\n";

    link.EnablePcapAll("ntn-traffic");

    Simulator::Schedule(
        Seconds(1.0),
        &SendTraffic,
        sender,
        sizes,
        intervals,
        0,
        0.0);

    Simulator::Stop(Seconds(20.0));
    Simulator::Run();

    Ptr<PacketSink> sink =
        DynamicCast<PacketSink>(sinkApps.Get(0));

    std::cout << "Packets generated: " << packetCount << std::endl;
    std::cout << "Total application bytes received: "
              << sink->GetTotalRx() << std::endl;
    std::cout << "Simulation completed successfully." << std::endl;

    csv.close();
    Simulator::Destroy();

    return 0;
}
