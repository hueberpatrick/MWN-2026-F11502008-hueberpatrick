Literature Review

Project: QoS Performance Analysis of 5G Non-Terrestrial Networks Using SNS3

Research focus: Impact of network load and satellite-link conditions on end-to-end latency

⸻

Table of Contents

1. On the Queuing Delay of Time-Varying Channels in Low Earth Orbit Satellite Constellations
    * 1.1 Problem, importance, challenges and proposed method
    * 1.2 System model
    * 1.3 Experimental results
    * 1.4 Parameters required for reproducing the experiments
    * 1.5 What this means for my project
2. NS-3-based 5G Satellite-Terrestrial Integrated Network Simulator
    * 2.1 Problem, importance, challenges and proposed method
    * 2.2 System model
    * 2.3 Experimental results
    * 2.4 Parameters required for reproducing Figure 4
    * 2.5 What this means for my project
3. Comparison of the two papers
4. Revised A1 Project Proposal
5. Experimental Plan Using SNS3
6. Limitations and Future Work
7. References

⸻

1. On the Queuing Delay of Time-Varying Channels in Low Earth Orbit Satellite Constellations

Source: IEEE Xplore

N. J. Hernández Marcano, L. Díez, R. Agüero Calvo and R. H. Jacobsen, “On the Queuing Delay of Time-Varying Channels in Low Earth Orbit Satellite Constellations,” IEEE Access, vol. 9, pp. 87378–87390, 2021.

DOI: 10.1109/ACCESS.2021.3089005

1.1 Problem, Importance, Challenges and Proposed Method

Problem

Low Earth Orbit (LEO) satellite constellations are becoming increasingly important for providing communication services in remote areas and supporting future 5G and 6G networks.

Although LEO satellites operate at much lower altitudes than geostationary satellites, communication delays remain an important performance limitation.

Traditional satellite-network models often assume relatively stable channel conditions. However, real satellite communication links can experience time-varying propagation conditions, particularly between satellites and ground stations.

These variations affect transmission capacity, packet queues and end-to-end latency.

The central problem investigated in this paper is:

How do time-varying satellite channels and network traffic affect queuing delay and end-to-end latency in LEO satellite constellations?

Importance

End-to-end latency is a critical Quality of Service (QoS) metric for modern communication systems.

Applications such as real-time monitoring, industrial automation, interactive services and remote control depend on predictable packet delivery times.

LEO satellite networks can improve geographical coverage, but this does not automatically guarantee low or stable latency.

Even if propagation delay is relatively small, packets can experience additional waiting times when network links become congested or their transmission capacity decreases.

The paper therefore investigates both the average delay and its statistical distribution.

Challenges

1. Time-varying channels: Satellite-to-ground connections experience changing propagation conditions that affect available transmission capacity.
2. Multiple satellite hops: Packets may travel through several satellites before reaching their destination.
3. Traffic aggregation: Several communication flows can share satellite links, creating congestion and queues.
4. Delay variability: Average latency alone does not describe the worst-case behavior of the network.
5. Mathematical complexity: The interaction between channel states and packet queues requires a more advanced analytical model than a constant-capacity link.

Proposed Method

The authors introduce an analytical queuing model that represents a communication path through a LEO satellite constellation.

The model distinguishes between two link types:

* Ground-to-satellite and satellite-to-ground links with time-varying Land Mobile Satellite (LMS) channel conditions.
* Inter-Satellite Links (ISLs) with comparatively stable transmission conditions.

For the LMS links, the authors use a Markov-based model with three channel states:

Channel state	Description	Effect
Line of Sight (LoS)	Favorable propagation conditions	Highest transmission capacity
Mid-Shadowing	Moderate signal degradation	Reduced transmission capacity
Deep-Shadowing	Severe signal degradation	Strongly reduced transmission capacity

Inter-satellite links are represented using M/M/1 queuing models.

The analytical results are validated against an event-driven simulator implemented in C++.

Important distinction: The simulator used in this paper is not SNS3. Its queuing model and experimental findings can nevertheless inform the design of an SNS3 experiment.

1.2 System Model

Environment

The investigated environment is a LEO satellite constellation connecting two ground stations.

A communication path contains an uplink from the transmitting ground station, multiple inter-satellite connections and a downlink to the receiving ground station.

For the end-to-end analysis, the authors investigate a path involving six satellites.

The network topology is treated as a static snapshot during the relatively short queuing-delay observation period.

This simplifies the analysis because orbital movement occurs over a much longer timescale than individual packet transmissions.

Network Topology

The communication path can be represented as:

Ground Station A → Satellite 1 → Satellite 2 → ... → Satellite 6 → Ground Station B

The individual connections are:

* Uplink: Ground Station A to Satellite 1
* Inter-Satellite Links: Connections between neighboring satellites
* Downlink: Satellite 6 to Ground Station B

The uplink and downlink use the time-varying LMS channel model.

The inter-satellite connections are assumed to have stable Line-of-Sight conditions.

Assumptions

* The satellite path is fixed during the investigated time interval.
* Packets are processed according to First-Come, First-Served (FCFS).
* The analytical model uses infinite packet buffers.
* Inter-satellite links are modeled as M/M/1 queues.
* Uplink and downlink channel conditions change over time.
* Initial analytical validation uses Poisson packet arrivals.
* The simulator also permits experiments with alternative traffic distributions.

Inputs

Input parameter	Description
Packet arrival rate, λ	Number of incoming packets per second
Packet length	Average packet size
Satellite-link capacity	Maximum transmission rate
Elevation angle	Angle between ground station and satellite
Channel state	LoS, Mid-Shadowing or Deep-Shadowing
Background traffic	Additional traffic sharing network links
Number of satellite hops	Length of the communication path
Traffic distribution	Statistical characteristics of packet arrivals

Outputs

* Average queuing delay
* Average end-to-end delay
* Packet delay distribution
* Queue occupancy
* Delay variability
* Delay percentiles

Performance Metrics

The main metric is total end-to-end delay:

[
D_{\text{E2E}}=D_{\text{propagation}}+D_{\text{transmission}}+D_{\text{queueing}}
]

For a path consisting of multiple links, the individual delay components must be accumulated across the path.

The average delay is:

[
\overline{D}=\frac{1}{N}\sum_{i=1}^{N}D_i
]

where (D_i) is the delay of packet (i).

The standard deviation can be used to quantify delay variability:

[
\sigma_D=\sqrt{\frac{1}{N}\sum_{i=1}^{N}(D_i-\overline{D})^2}
]

These metrics are particularly relevant for evaluating QoS.

1.3 Experimental Results

The authors compare analytical predictions with results from an event-driven simulation framework.

Several experiments investigate different packet arrival rates, packet sizes and satellite-channel conditions.

Experiment 1: Validation of the LMS Queuing Model

The first experiments verify whether the proposed model correctly describes packet queues under changing channel conditions.

The analytical results are compared with simulated queue occupancy and packet delays.

Finding: The model and simulation show close agreement under the investigated stable operating conditions.

This supports the validity of the proposed mathematical approach.

Experiment 2: Effect of Traffic Load

The packet arrival rate is increased while the channel characteristics remain defined.

As more packets enter the network, the utilization of the communication links increases.

At low traffic loads, packets experience relatively short waiting times.

When the arrival rate approaches the effective service capacity, queuing delay increases considerably.

Finding: Network load has a strong influence on latency, particularly when satellite links temporarily operate at reduced capacity.

Experiment 3: Delay Distribution

Figure 8 presents a box-and-whisker analysis of packet delays for different traffic conditions.

The experiments use a large packet sample to investigate not only average latency but also the distribution of delays.

The paper reports that the 95th-percentile delay can be approximately twice the average delay under some investigated conditions.

Finding: Average latency can hide significant delay variations.

This is particularly important for delay-sensitive applications.

Experiment 4: End-to-End Delay

Figure 9 investigates the complete communication path between two ground stations.

The authors compare different average packet sizes and arrival rates.

The analysis includes the effects of the uplink, inter-satellite links and downlink.

Finding: Ground-to-satellite and satellite-to-ground channel conditions have a stronger effect on end-to-end delay and its variability than the comparatively stable inter-satellite connections.

Summary of Results

Experiment	Varied parameter	Main finding
LMS queue validation	Channel conditions and arrival rate	Analytical and simulated results agree closely
Traffic-load analysis	Packet arrival rate	Queuing delay increases with load
Delay distribution	Traffic load	High-percentile delays can greatly exceed the mean
End-to-end analysis	Packet size and arrival rate	Ground-satellite links strongly influence latency
Background traffic analysis	Additional traffic	Shared traffic can substantially increase delay

1.4 Parameters Required for Reproducing the Experiments

The following table distinguishes between reported values and information that must be recovered from the original model configuration or simulator.

Parameter	Value from the paper	Reproduction status
Network type	LEO satellite constellation	Reported
Ground stations	2	Reported
Satellites in E2E path	6	Reported
Inter-satellite links	5	Reported
Frequency band	S-band	Reported
Carrier frequency	2.6 GHz	Reported
Ideal link capacity	5 Mbps	Reported
Mid-Shadowing capacity	10% of ideal capacity	Reported
Deep-Shadowing capacity	1% of ideal capacity	Reported
Packet lengths	100 and 1000 bytes	Reported
Traffic model	Poisson arrivals for analytical validation	Reported
Packet inter-arrival distribution	Exponential for Poisson traffic	Reported
Satellite-to-ground channel	Three-state LMS model	Reported
Inter-satellite queuing model	M/M/1	Reported
Queue discipline	FCFS	Reported
Buffer capacity	Infinite in analytical model	Reported
Elevation angle	Different values; 80° in selected experiments	Reported
Packets per run, Fig. 8	1,000,000	Reported
Independent runs, Fig. 9	100	Reported
Packets per run, Fig. 9	10,000	Reported
Simulation implementation	Event-driven C++ simulator	Reported
Simulation duration in seconds	Not established from the reviewed configuration	Open
Random seed values	Not established from the reviewed configuration	Open
Exact LMS transition probabilities	Dependent on referenced channel model and elevation	Requires model tables
Satellite altitude for the selected reproduction	Must be extracted from the relevant constellation configuration	Open

Reproduction Strategy

A complete numerical reproduction would require matching the LMS channel-state transition probabilities, the satellite geometry and the traffic generation process.

For my own project, I do not intend to reproduce the complete analytical queuing framework.

Instead, I will use the paper to identify the parameters that should be investigated in an SNS3-based satellite simulation.

The most relevant parameters are:

1. Network traffic load
2. Satellite-link conditions
3. End-to-end latency
4. Delay variability

Reproduction Limitations

The paper uses a specialized event-driven simulator rather than SNS3.

Therefore, its numerical results cannot automatically be expected from an SNS3 experiment.

Differences may arise from channel models, satellite topology, queue implementations and protocol behavior.

A qualitative comparison is a more realistic initial objective.

1.5 What This Means for My Project

The paper provides several important conclusions for my planned NTN simulation.

1. Network load should be a primary input variable.

Increasing traffic can produce substantial queuing delays even when the physical propagation delay remains unchanged.

Therefore, varying the number of active users or the offered traffic load is relevant for my project.

2. Mean latency is not sufficient to describe QoS.

A network with acceptable average latency may still experience occasional packets with very large delays.

I should therefore consider additional metrics such as delay standard deviation and the 95th-percentile delay.

3. Satellite-link conditions matter.

The results demonstrate that ground-to-satellite links are important sources of delay variability.

This suggests that satellite elevation or link conditions could be investigated in future experiments.

4. A simple baseline is preferable.

The paper contains a sophisticated analytical model.

For my initial SNS3 experiment, I will use a simpler topology and a limited number of input variables.

5. My A1 proposal should be more specific.

Instead of investigating general QoS performance without a clearly defined experiment, I will focus on the relationship between network load and end-to-end latency in a LEO satellite scenario.

⸻

2. NS-3-based 5G Satellite-Terrestrial Integrated Network Simulator

Source: IEEE Xplore

N. Badini, M. Marchese and F. Patrone, “NS-3-based 5G Satellite-Terrestrial Integrated Network Simulator,” 2022 IEEE 21st Mediterranean Electrotechnical Conference (MELECON), Palermo, Italy, 2022.

DOI: 10.1109/MELECON53508.2022.9843098

2.1 Problem, Importance, Challenges and Proposed Method

Problem

Future 5G communication systems are expected to provide reliable connectivity in a wide variety of geographical environments.

However, terrestrial networks alone cannot guarantee coverage everywhere.

Satellites can extend network coverage to remote regions, maritime environments and other locations without sufficient terrestrial infrastructure.

The integration of satellites into 5G systems introduces additional challenges related to mobility, handover, propagation delay and resource management.

A suitable simulation environment is necessary to evaluate these mechanisms before deploying real systems.

The central problem addressed by this paper is:

How can 5G satellite-terrestrial integrated networks be modeled and evaluated using an open-source system-level simulator?

Importance

System-level simulation allows researchers to investigate network behavior without constructing expensive satellite communication infrastructure.

It also supports comparisons between different network configurations.

For 5G NTN, simulation is particularly important because satellites introduce characteristics that are not present in conventional terrestrial cellular networks.

These include:

* Large propagation distances
* Satellite movement
* Changing satellite visibility
* Handover between satellite cells
* Different application requirements
* Dynamic radio-resource allocation

The paper is relevant because it introduces a practical simulation approach based on ns-3.

Challenges

1. Satellite mobility: LEO satellites continuously move relative to ground users.
2. Handover: A user may need to switch from one satellite gNB to another.
3. Propagation delay: Satellite communication links are longer than conventional terrestrial links.
4. Traffic differentiation: Different applications require different levels of latency, throughput and reliability.
5. Radio-resource management: Available spectrum must be allocated efficiently between users.
6. Simulation complexity: Detailed satellite-terrestrial simulations can require significant computational resources.

Proposed Method

The authors present a system-level simulator based on ns-3 for integrated 5G satellite-terrestrial networks.

A central feature is the possibility of representing satellites as 5G base stations, referred to as satellite gNBs.

The simulator supports:

* Satellite-based gNBs
* Terrestrial user equipment (UE)
* Satellite handover
* Dynamic Bandwidth Part (BWP) configuration
* Component Carrier (CC) configuration
* Different traffic profiles
* Evaluation of packet delivery time

The authors also introduce a mechanism for assigning radio resources according to the performance requirements of different traffic profiles.

Users with similar requirements can be grouped and assigned suitable spectrum resources.

Important distinction: The proposed simulator is based on ns-3 and 5G simulation components. It is not identical to SNS3. The two environments must not be treated as interchangeable without verifying their supported features.

2.2 System Model

Environment

The investigated system is an integrated 5G network containing LEO satellites and terrestrial users.

Satellites operate as gNBs and provide communication services to user equipment on the ground.

The simulation includes a remote host and a core-network connection.

The authors compare satellite-based communication with a terrestrial 5G reference scenario.

Network Topology

The main communication path can be represented as:

Remote Host → Core Network → Satellite gNB → User Equipment

The scenario includes two satellite gNBs.

The number of terrestrial users is varied between one and six.

Users are associated with satellite gNBs according to the simulator’s handover and connection mechanisms.

At least one handover occurs during the simulation.

Assumptions

* Satellites operate in LEO.
* Satellites can function as 5G gNBs.
* The satellite orbits are circular.
* A minimum elevation angle is required for communication.
* User equipment is located on the ground.
* Traffic is generated by a remote host.
* One traffic flow is configured per UE.
* Different traffic profiles can be represented.
* Satellite handover is included.

Inputs

Input	Description
Number of UEs	Network load represented by the number of users
Satellite altitude	Orbital height
Orbital inclination	Satellite orbital geometry
Minimum elevation angle	Minimum angle required for connectivity
Traffic profile	Application-related performance requirements
Packet size	Amount of data in each packet
Number of packets	Total generated traffic
gNB type	Satellite or terrestrial
Simulation duration	Length of the simulated scenario

Outputs

* Average Delivery Time (ADT)
* Packet transmission and reception timestamps
* Handover-related behavior
* Network performance under different user counts

Performance Metric: Average Delivery Time

The main performance metric is the Average Delivery Time:

[
ADT=\frac{1}{P}\sum_{p=1}^{P}(T_{RX,p}-T_{TX,p})
]

where:

* (P) is the number of generated packets,
* (T_{TX,p}) is the transmission time of packet (p),
* (T_{RX,p}) is the reception time of packet (p).

ADT measures the average time between sending a packet at the remote host and receiving it at the UE.

This metric is closely related to the end-to-end latency that I intend to investigate.

For a complete implementation, lost packets must be handled separately rather than assigning them an artificial reception time.

2.3 Experimental Results

Experiment: Satellite versus Terrestrial 5G

The authors compare the Average Delivery Time of two network configurations:

1. A terrestrial 5G network with conventional gNBs
2. A satellite-based 5G network with LEO satellite gNBs

The number of UEs is varied.

Figure 4 presents the resulting ADT.

Result 1: Satellite Networks Have Higher Delivery Times

The satellite-based scenario shows higher packet delivery times than the terrestrial reference.

This is primarily explained by the additional propagation distance of satellite links.

The packet path includes satellite communication links between the user, the satellite gNB and the core network.

Finding: Satellite integration improves geographical coverage but introduces additional propagation delay.

Result 2: Satellite Geometry Influences Propagation Delay

The authors calculate propagation delay for the investigated satellite altitude and minimum elevation angle.

With a satellite altitude of 600 km and a minimum elevation angle of 20°, the relevant satellite-link distance ranges from approximately 600 km to 1392 km.

This corresponds to a one-way propagation delay of approximately 2 to 4.64 ms for an individual satellite link.

These values represent propagation delay, not the total packet delivery time.

Finding: Satellite geometry is an important contributor to end-to-end latency.

Result 3: Network Performance Can Be Evaluated for Different User Counts

The number of UEs is varied between one and six.

This allows the authors to investigate packet delivery performance as the number of connected users changes.

Finding: The experiment demonstrates how a satellite-based 5G simulator can evaluate different network configurations and user populations.

The paper does not establish a universal relationship between user count and latency for every NTN scenario.

Result 4: Handover Is Included

The simulated satellites move relative to the terrestrial UEs.

During the two-second experiment, at least one UE changes its serving satellite gNB.

This demonstrates that the simulator can represent satellite mobility and handover.

Finding: Handover is an important capability for realistic LEO network simulations.

However, the paper’s primary presented performance comparison focuses on ADT rather than a detailed statistical analysis of handover interruption time.

Summary of Results

Investigation	Parameter	Finding
Satellite vs. terrestrial	gNB type	Satellite-based communication has higher ADT
User-count comparison	1–6 UEs	ADT can be evaluated for different user populations
Propagation analysis	600 km altitude, 20° elevation	Individual satellite-link propagation delay approximately 2–4.64 ms
Satellite mobility	Moving satellite gNBs	Handover occurs during the simulation
Traffic differentiation	Traffic profiles	Simulator supports differentiated resource configurations

2.4 Parameters Required for Reproducing Figure 4

The following values are reported in Table I of the paper.

Network and Satellite Configuration

Parameter	Value
Number of satellite gNBs	2
Number of terrestrial UEs	1–6
Number of traffic profiles	2
Number of UEs per traffic profile	2
Satellite altitude	600 km
Orbital eccentricity	0
Orbital inclination	88°
Argument of perigee	90°
Minimum elevation angle	20°
Simulation duration	2 s

Traffic Configuration

Parameter	Value
Number of transmitted packets	960
Packet size	1280 bytes
Traffic flows	One per UE
Traffic direction	Remote host to UE
Source	Remote host on the ground
Destination	Terrestrial UE
Handover	At least one event after approximately 1 s

PHY/MAC and Reproducibility Information

Parameter	Information	Status
Network technology	5G NR-based satellite-terrestrial system	Reported
Simulator	ns-3-based system-level simulator	Reported
Satellite role	Satellite gNB	Reported
Resource configuration	BWP and CC mechanisms	Described
Traffic-profile count	2	Reported
Exact carrier frequency for Fig. 4	Not established from Table I	Open
Exact channel bandwidth	Not established from Table I	Open
Numerology for each traffic profile	Not established from Table I	Open
Modulation and coding configuration	Not established from Table I	Open
MAC scheduler settings	Not established from Table I	Open
Packet inter-arrival distribution	Not established from Table I	Open
Random seeds	Not established from Table I	Open
Number of independent runs	Not established from Table I	Open
Exact simulator revision	Must be matched to the authors’ implementation	Open

Reproduction Strategy

To reproduce the ADT comparison, the following steps would be required:

1. Configure two LEO satellite gNBs.
2. Set the satellite altitude to 600 km.
3. Configure the specified orbital parameters.
4. Set the minimum elevation angle to 20°.
5. Create one to six terrestrial UEs.
6. Configure a remote host and one downlink traffic flow per UE.
7. Generate packets according to the reported packet count and size.
8. Enable satellite movement and handover.
9. Run the two-second simulation.
10. Record transmission and reception timestamps.
11. Calculate the Average Delivery Time.
12. Compare the results with the terrestrial reference.

A numerical reproduction would additionally require the missing PHY/MAC and traffic-generation details.

Reproduction Limitations

The original paper uses a specific ns-3-based 5G satellite simulator.

My planned project uses SNS3, which may provide a different set of models and configuration interfaces.

Therefore, the paper’s simulation cannot automatically be reproduced by copying the same numerical parameters into SNS3.

The satellite topology, supported radio models and traffic configuration must first be verified.

For A3, I will use the paper primarily as a reference for experimental design and QoS measurement.

2.5 What This Means for My Project

1. The number of users is a useful experimental input.

The paper demonstrates a systematic comparison with different numbers of connected UEs.

I can adopt this idea for my SNS3 experiment.

2. Average packet delivery time is a suitable output metric.

ADT provides a clearly defined measurement of network latency.

I can use a similar definition for end-to-end delay.

3. A fixed satellite configuration simplifies the experiment.

The authors use a defined altitude and orbital configuration.

For my initial experiment, I will keep satellite altitude and other orbital parameters fixed while varying network load.

4. Satellite propagation delay must be considered.

The paper shows that even a 600 km LEO satellite introduces measurable propagation delay.

This is an important difference from terrestrial communication networks.

5. Handover can affect latency.

The simulator includes handover events.

For my initial project, I will investigate whether SNS3 supports an appropriate handover model.

If this is too complex, I will first focus on a fixed communication path.

6. The experiment should remain manageable.

The paper uses a relatively small scenario with two satellites and a limited number of users.

This supports my decision to start with a simple network topology rather than a complete satellite constellation.

⸻

3. Comparison of the Two Papers

Both papers investigate performance-related aspects of satellite communication networks, but they approach the problem differently.

Criterion	Paper 1: Marcano et al.	Paper 2: Badini et al.
Publication	IEEE Access, 2021	IEEE MELECON, 2022
Main focus	Queuing delay in LEO networks	5G satellite-terrestrial simulation
Network type	LEO satellite constellation	Integrated 5G NTN
Method	Analytical model and C++ simulation	ns-3-based system-level simulation
Main input	Traffic load and channel conditions	Number of UEs and network configuration
Main output	Queuing and end-to-end delay	Average Delivery Time
Satellite mobility	Static path snapshot for delay analysis	Satellite mobility and handover
Traffic model	Poisson and other statistical arrivals	Defined traffic profiles
Channel behavior	Time-varying LMS model	Satellite-based 5G links
Relevance to SNS3	Traffic and delay modeling	Simulation topology and QoS measurement

3.1 Common Findings

The papers agree that satellite communication introduces additional performance challenges compared with conventional terrestrial networks.

Both show that satellite-link characteristics influence packet delivery time.

Both also demonstrate the importance of simulation for evaluating network performance.

However, they emphasize different aspects.

Paper 1 focuses on the interaction between traffic load, channel variability and packet queues.

Paper 2 focuses on system-level modeling of 5G satellite-terrestrial networks and practical performance evaluation.

3.2 Complementary Contributions

Paper 1 explains why latency can increase under traffic load even when propagation conditions remain unchanged.

Paper 2 provides a concrete example of how a satellite-based 5G scenario can be configured and evaluated.

Together, the papers motivate an experiment that varies network load while keeping satellite geometry fixed.

This makes it possible to investigate whether increasing traffic leads to measurable changes in end-to-end latency.

3.3 Remaining Research Gap

Neither paper directly demonstrates the exact experiment I intend to perform using SNS3.

The first paper uses a specialized queuing simulator.

The second uses a different ns-3-based satellite-terrestrial simulation framework.

Therefore, the main objective of my project is not to claim a new theoretical discovery.

Instead, it is to build a reproducible satellite-network experiment and evaluate QoS behavior under controlled traffic conditions.

⸻

4. Revised A1 Project Proposal

4.1 Original Project Idea

Original title:

QoS Performance Analysis of 5G Non-Terrestrial Networks Using ns-3

The initial project idea was to investigate the performance of satellite communication networks and determine how different network parameters influence QoS.

The original scope included satellite communication characteristics and different traffic conditions.

However, the precise simulator configuration, input variables and output metrics had not yet been finalized.

4.2 Revised Project Title

Impact of Network Load on End-to-End Latency in LEO Satellite Networks Using SNS3

This revised title reflects a more focused experiment and the planned simulator.

4.3 Revised Research Question

How does increasing network traffic load affect the end-to-end latency of packets in a LEO satellite communication network?

The experiment will investigate this relationship under a fixed satellite configuration.

4.4 Revised Project Objective

The objective is to develop a reproducible SNS3 simulation scenario and measure how end-to-end latency changes when network load increases.

The project will use a simplified LEO satellite communication topology.

Satellite geometry and link configuration will initially remain fixed.

Network load will be varied systematically.

The resulting packet delays will be recorded and analyzed.

4.5 Changes Compared with A1

Aspect	Original A1 proposal	Revised A3 proposal	Reason
Simulator	ns-3	SNS3, subject to feature verification	Better alignment with satellite-specific simulation
Research scope	General NTN QoS	Network load versus latency	More focused and measurable
Satellite configuration	Not finalized	Fixed LEO baseline	Reduces experimental complexity
Input variables	Broadly defined	Number of users and traffic load	Motivated by both papers
Main output	Latency	Mean end-to-end latency	Clearly defined performance metric
Additional metrics	Not finalized	Delay variability and 95th percentile, if feasible	Motivated by Paper 1
Experimental approach	General simulation	Controlled parameter sweep	Improves reproducibility
Reproduction	Not specified	Document topology, traffic, PHY/MAC, duration and seeds	Follows A3 requirements

4.6 Why These Changes Were Made

The literature review shows that a narrowly defined experiment is preferable to a broad investigation of all NTN QoS parameters.

Paper 1 demonstrates that traffic load and queuing behavior can strongly influence packet delay.

Paper 2 demonstrates how satellite-based network performance can be measured using packet delivery timestamps and a controlled number of users.

Therefore, the revised project focuses on traffic load as the main experimental factor.

Using SNS3 is intended to provide a satellite-specific simulation environment.

However, simulator capabilities must be verified before the final experiment is implemented.

⸻

5. Experimental Plan Using SNS3

This section describes the proposed future experiment. No SNS3 experiment has been executed for A3.

5.1 Proposed System Model

The initial experiment will use a simple satellite communication topology.

A source node sends UDP packets through a satellite link to a receiving node.

The exact implementation will depend on the SNS3 examples and available network models.

A conceptual topology is:

Traffic Sources → Ground/Satellite Access → LEO Satellite Network → Destination

The satellite configuration will remain fixed during the first parameter sweep.

5.2 Independent Variables

Two inputs are proposed.

Input 1: Number of Active Users

Possible values:

Scenario	Active users
A	1
B	5
C	10
D	20

These values are proposed experimental settings, not values taken directly from either paper.

Input 2: Offered Traffic Load

Possible traffic-generation rates per user:

Traffic level	Offered rate per user
Low	100 kbps
Medium	500 kbps
High	1 Mbps

The exact rates will be adjusted according to the capacity and supported traffic models of the selected SNS3 scenario.

A two-dimensional parameter sweep could compare all combinations of user count and offered rate.

5.3 Fixed Parameters

Parameter	Proposed configuration
Satellite orbit	LEO
Satellite altitude	600 km, if supported by the selected scenario
Traffic protocol	UDP
Packet size	1000 bytes initially
Satellite configuration	Fixed during the load sweep
Traffic distribution	Constant rate initially
Simulation duration	To be determined after simulator validation
Random seeds	Multiple documented runs
Main performance metric	Mean end-to-end latency

The altitude is motivated by Paper 2.

The packet size is a practical baseline choice motivated by Paper 1.

These settings are not yet a validated SNS3 configuration.

5.4 Output Metrics

Primary Metric: End-to-End Latency

For each successfully received packet:

[
D_i=t_{\mathrm{RX},i}-t_{\mathrm{TX},i}
]

The mean delay is:

[
\overline{D}=\frac{1}{N_{\mathrm{RX}}}
\sum_{i=1}^{N_{\mathrm{RX}}}D_i
]

where (N_{\mathrm{RX}}) is the number of successfully received packets.

Secondary Metric: Delay Variability

[
\sigma_D=\sqrt{
\frac{1}{N_{\mathrm{RX}}}
\sum_{i=1}^{N_{\mathrm{RX}}}
(D_i-\overline{D})^2
}
]

This metric indicates how strongly packet delays vary.

Additional Metric: Packet Delivery Ratio

[
PDR=\frac{N_{\mathrm{RX}}}{N_{\mathrm{TX}}}\times100%
]

PDR is useful because average latency alone does not account for lost packets.

5.5 Proposed Simulation Procedure

1. Install and verify a compatible SNS3 version.
2. Run an existing satellite communication example.
3. Identify the available traffic-generation and tracing interfaces.
4. Configure a small baseline topology.
5. Generate UDP traffic.
6. Record packet transmission and reception timestamps.
7. Verify that latency measurements are correct.
8. Increase the number of users.
9. Repeat the experiment for different traffic loads.
10. Repeat runs using documented random seeds.
11. Export results to CSV.
12. Analyze the results using Python.
13. Create comparison plots.
14. Discuss the results in relation to the two IEEE papers.

5.6 Expected Results

Based on the literature, I expect end-to-end latency to increase when network load approaches the available link capacity.

At low traffic loads, delay may be dominated by propagation and transmission.

At higher loads, packet queues may contribute more strongly to total delay.

Delay variability may also increase as congestion becomes more significant.

These are hypotheses derived from the reviewed literature.

They are not experimental findings from my own SNS3 simulation.

⸻

6. Limitations and Future Work

6.1 Limitations of the Literature Review

The two papers investigate different simulation frameworks.

Consequently, their results are not directly interchangeable.

The first paper provides detailed queuing models but does not use a full 5G NR protocol simulation.

The second paper uses an ns-3-based 5G satellite-terrestrial simulator, but not all configuration details needed for exact numerical reproduction are established in the reviewed material.

In particular, some PHY/MAC parameters, random seeds and software-version details require further verification.

6.2 Limitations of the Proposed Experiment

The initial experiment will use a simplified satellite scenario.

It may not capture all characteristics of operational 5G NTN systems.

Potential limitations include:

* Simplified satellite topology
* Limited number of users
* Fixed orbital configuration
* Simplified traffic generation
* Limited modeling of realistic application behavior
* Simulator-specific channel and protocol assumptions
* Possible omission of mobility and handover in the first baseline

These limitations will be documented rather than hidden.

6.3 Future Improvements

After establishing a working baseline, the project could be extended to investigate:

1. Different satellite altitudes
2. Different elevation angles
3. Time-varying channel conditions
4. Bursty traffic models
5. Satellite mobility and handover
6. Delay percentiles and jitter
7. Packet loss and throughput
8. Different QoS traffic classes

A more advanced implementation could compare multiple application types with different latency requirements.

⸻

7. References

[1] N. J. Hernández Marcano, L. Díez, R. Agüero Calvo and R. H. Jacobsen, “On the Queuing Delay of Time-Varying Channels in Low Earth Orbit Satellite Constellations,” IEEE Access, vol. 9, pp. 87378–87390, 2021. DOI: 10.1109/ACCESS.2021.3089005.

https://ieeexplore.ieee.org/document/9454162

[2] N. Badini, M. Marchese and F. Patrone, “NS-3-based 5G Satellite-Terrestrial Integrated Network Simulator,” 2022 IEEE 21st Mediterranean Electrotechnical Conference (MELECON), Palermo, Italy, 2022. DOI: 10.1109/MELECON53508.2022.9843098.

https://ieeexplore.ieee.org/document/9843098

⸻

Conclusion

This literature review investigated two complementary approaches to analyzing satellite communication performance.

The first paper demonstrated that traffic load, channel variability and packet queues can significantly influence end-to-end latency in LEO satellite constellations.

The second paper demonstrated the use of an ns-3-based system-level simulator to evaluate 5G satellite-terrestrial communication, including satellite mobility and Average Delivery Time.

Together, the papers provide the motivation for a focused simulation experiment investigating the relationship between network load and end-to-end latency.

Based on these findings, my original project proposal has been revised to focus on a reproducible SNS3-based LEO satellite scenario.

The next project phase will verify the simulator environment, implement the baseline and measure QoS performance under different traffic conditions.

No new experiment was required or performed for A3.
