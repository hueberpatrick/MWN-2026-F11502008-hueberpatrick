Literature Review

Project: QoS Performance Analysis of 5G Non-Terrestrial Networks Using SNS3
Focus: Network load, satellite-link conditions, and end-to-end latency

Contents

• 1. Queuing Delay in LEO Satellite Constellations
  • 1.1 Problem, importance, challenges, method
  • 1.2 System model
  • 1.3 Experimental results
  • 1.4 Reproduction parameters
  • 1.5 Implications for my project
• 2. NS-3-based 5G Satellite-Terrestrial Integrated Network Simulator
  • 2.1 Problem, importance, challenges, method
  • 2.2 System model
  • 2.3 Experimental results
  • 2.4 Reproduction parameters
  • 2.5 Implications for my project
• 3. Comparison
• 4. Revised A1 Project Proposal
• 5. Proposed SNS3 Experiment
• 6. Limitations and Future Work
• 7. References

> **Reproducibility note:** “Reported” refers to values identified in the reviewed material. “To verify” means the exact value has not been established here; it must not be presented as a published experimental setting. Proposed SNS3 values are explicitly separated from paper settings. **No SNS3 experiment was required or performed for A3.**

────────

1. Queuing Delay in LEO Satellite Constellations

Paper: On the Queuing Delay of Time-Varying Channels in Low Earth Orbit Satellite Constellations (IEEE Access, 2021).
Source: https://ieeexplore.ieee.org/document/9454162
DOI: https://doi.org/10.1109/ACCESS.2021.3089005

1.1 Problem, importance, challenges, method

Problem. LEO satellites reduce propagation distances compared with GEO systems, but their packet delivery times are still affected by variable ground-to-satellite channels and congestion. A fixed propagation-delay estimate cannot explain packet waiting times under fluctuating service capacity.

Importance. Real-time applications require not only a low mean delay but also predictable delivery. Queueing delay can dominate the performance of a satellite path when offered traffic approaches the effective link capacity.

Challenges:

1. The ground-satellite channel varies between favorable and degraded conditions.
2. Several satellite hops contribute to end-to-end delay.
3. Background traffic shares link capacity and creates queues.
4. A mean delay can conceal a long tail of slow packets.
5. Analytical queue models must be checked against simulation.

Proposed method. The authors combine a time-varying Land Mobile Satellite (LMS) channel/queue model for ground-satellite connections with queueing models for inter-satellite links (ISLs). They validate the analysis using an event-driven C++ simulator.

|Channel condition  |Interpretation             |Expected impact                                       |
|-------------------|---------------------------|------------------------------------------------------|
|Line of Sight (LoS)|Favorable signal path      |High available service capacity                       |
|Mid-Shadowing      |Moderately degraded channel|Lower service capacity and potential queue growth     |
|Deep-Shadowing     |Strongly degraded channel  |Very low service capacity and potentially large delays|

The study concerns satellite queueing; it is not an SNS3 or 5G NR simulation.

1.2 System model

Environment: A communication route between two ground stations via a LEO constellation. The path contains an uplink, multiple ISLs, and a downlink. A fixed route snapshot is used for the queueing analysis.

flowchart LR
    A[Ground station A] --> U[Uplink: time-varying LMS]
    U --> S1[LEO satellite 1]
    S1 --> I[Inter-satellite links]
    I --> S6[LEO satellite 6]
    S6 --> D[Downlink: time-varying LMS]
    D --> B[Ground station B]

Assumptions:

• First-come, first-served packet processing.
• Poisson arrivals in the analytical validation scenarios.
• An idealized queueing representation; actual physical and protocol behavior is simplified.
• ISLs have more stable conditions than the modeled ground-satellite channels.
• The analysis separates the effects of arrival rates and service rates.

Inputs and outputs:

|Category|Variable              |Meaning                                    |
|--------|----------------------|-------------------------------------------|
|Input   |Arrival rate $\lambda$|Offered packets per second                 |
|Input   |Packet length         |Payload affecting transmission service time|
|Input   |Channel state         |LoS / Mid-Shadowing / Deep-Shadowing       |
|Input   |Link capacity         |Maximum service rate of a connection       |
|Input   |Background traffic    |Competing packet flows                     |
|Input   |Satellite path        |Number and type of traversed links         |
|Output  |Queueing delay        |Time spent waiting for service             |
|Output  |End-to-end delay      |Total packet travel time                   |
|Output  |Delay distribution    |Variability and tail of delay              |

Performance metrics. A useful conceptual decomposition is:

$$
D_{\mathrm{E2E}} = D_{\mathrm{propagation}} + D_{\mathrm{transmission}} + D_{\mathrm{queueing}}.
$$

For $N$ received packets, mean delay and its standard deviation are:

$$
\overline{D} = \frac{1}{N}\sum_{i=1}^{N}D_i
$$

$$
\sigma_D = \sqrt{\frac{1}{N}\sum_{i=1}^{N}(D_i-\overline{D})^2}.
$$

These formulas describe metrics relevant to my proposed experiment; they are not claims that the paper uses precisely these symbols.

1.3 Experimental results

The paper compares analytical predictions with an event-driven simulator and examines how traffic and satellite channel conditions influence queueing and end-to-end delays.

|Investigation            |Varied factors                |Main interpretation                                               |
|-------------------------|------------------------------|------------------------------------------------------------------|
|Queueing-model validation|Traffic and channel parameters|Simulation is used to check the analytical predictions            |
|Load dependence          |Packet arrival rate           |Increasing load increases waiting time, particularly near capacity|
|Channel dependence       |LMS channel conditions        |Reduced service capacity creates larger and more variable queues  |
|End-to-end path          |Ground links and ISLs         |Ground-satellite link behavior matters for total delay            |
|Delay distribution       |Different traffic conditions  |Mean delay alone does not characterize the high-delay tail        |

Result interpretation. Even when the satellite path remains unchanged, additional offered traffic can increase queue occupancy and delay. This means that the number of active sources and their traffic rates are sensible experimental inputs for a QoS study.

Caution: Exact numerical claims about particular figures or percentiles should be checked against the full PDF before being quoted in a presentation. The literature review should not manufacture figure values.

1.4 Reproduction parameters

|Parameter                      |Paper setting / information                   |Status   |
|-------------------------------|----------------------------------------------|---------|
|Network                        |LEO satellite constellation                   |Reported |
|Ground stations                |2                                             |Reported |
|End-to-end route               |Path involving 6 satellites                   |Reported |
|Link types                     |Ground-satellite LMS and ISLs                 |Reported |
|Carrier frequency              |2.6 GHz (S-band)                              |Reported |
|Nominal link capacity          |5 Mbps in the referenced scenario             |Reported |
|Channel model                  |Three-state LMS model                         |Reported |
|Packet sizes                   |100 and 1000 bytes in studied settings        |Reported |
|Arrival process                |Poisson in analytical validation              |Reported |
|Queue model                    |FCFS; M/M/1-type ISL representation           |Reported |
|Channel-state transition matrix|Exact values needed for the selected figure   |To verify|
|Satellite orbital geometry     |Figure-specific configuration                 |To verify|
|PHY/MAC protocol details       |Not established for an exact SNS3 reproduction|To verify|
|Simulation time in seconds     |Figure-specific duration not established here |To verify|
|Random seeds                   |Exact seeds not established here              |To verify|
|Simulator                      |Event-driven C++ simulation                   |Reported |

Reproduction strategy. The main target is not to reimplement the full analytical LMS model. I will use this paper as a reference for the direction of the load–delay relationship and for selecting meaningful QoS metrics. Any numerical reproduction would require the complete channel transition model, the route configuration, and matching queue/service assumptions.

1.5 Implications for my project

1. Make network load a primary input. The paper explains why queueing delay rises when traffic approaches the link service capacity.
2. Measure more than the average. Delay standard deviation and the 95th percentile can reveal tail behavior.
3. Keep the baseline topology fixed. Changing orbit, channel and traffic simultaneously would make interpretation difficult.
4. Use a qualitative comparison first. SNS3 is not the simulator used in this study.
5. Revise A1 to a measurable question. The core question becomes the relationship between offered load and end-to-end packet latency.

────────

2. NS-3-based 5G Satellite-Terrestrial Integrated Network Simulator

Paper: NS-3-based 5G Satellite-Terrestrial Integrated Network Simulator (IEEE MELECON, 2022).
Source: https://ieeexplore.ieee.org/document/9843098
DOI: https://doi.org/10.1109/MELECON53508.2022.9843098

2.1 Problem, importance, challenges, method

Problem. Future 5G systems must provide coverage outside conventional terrestrial cellular infrastructure. Integrating satellites into 5G networks introduces long propagation distances, moving cells, changing visibility and resource-management requirements. Researchers need a system-level environment to study these effects.

Importance. An open-source simulator permits controlled evaluation without constructing an expensive satellite testbed. It can compare satellite and terrestrial configurations and provide reproducible performance measurements.

Challenges:

1. LEO satellites move relative to ground users.
2. Users may require handover between satellite gNBs.
3. Propagation delays differ from terrestrial 5G.
4. Traffic profiles can have different service requirements.
5. Spectrum and radio resources must be allocated to connected UEs.
6. System-level results depend on PHY/MAC and traffic configuration.

Proposed method. The authors develop an ns-3-based 5G satellite-terrestrial simulator in which satellites can act as gNBs. The framework represents satellite movement, UE connectivity, handover, and differentiated radio-resource configurations using component carriers (CCs) and bandwidth parts (BWPs).

Simulator distinction: This paper uses a specific ns-3-based 5G simulator, not SNS3. Its scenario is a useful methodological reference, not a drop-in SNS3 configuration.

2.2 System model

Environment: A satellite-terrestrial 5G scenario with LEO satellite gNBs, ground-based user equipment, a core-network connection, and a remote host sending application traffic.

flowchart LR
    RH[Remote host] --> CN[Core network]
    CN --> G1[LEO satellite gNB 1]
    CN --> G2[LEO satellite gNB 2]
    G1 --> UE[Ground user equipment]
    G2 -. handover .-> UE

Assumptions and setup:

• Satellites are modeled as 5G gNBs.
• Two satellite gNBs are included.
• The number of ground UEs is varied.
• Satellites follow a specified circular-orbit configuration.
• Communication requires a minimum elevation angle.
• A remote host sends packets to the UEs.
• Mobility and handover can occur within the simulated interval.

Inputs and outputs:

|Category|Variable                   |Meaning                          |
|--------|---------------------------|---------------------------------|
|Input   |Number of UEs              |Number of served users           |
|Input   |Satellite altitude         |Orbital height                   |
|Input   |Orbit inclination          |Orbital geometry                 |
|Input   |Elevation threshold        |Minimum usable satellite angle   |
|Input   |Packet size and count      |Application traffic configuration|
|Input   |Traffic profile            |Different service requirements   |
|Output  |Average Delivery Time (ADT)|Mean send-to-receive delay       |
|Output  |Handover behavior          |Changes in serving satellite     |
|Output  |Packet timestamps          |Basis for delay calculation      |

Primary performance metric: Average Delivery Time.

$$
ADT = \frac{1}{P}\sum_{p=1}^{P}\left(T_{RX,p}-T_{TX,p}\right)
$$

where:

• $P$ is the number of successfully received packets used in the delay average;
• $T_{TX,p}$ is the transmission timestamp of packet $p$;
• $T_{RX,p}$ is the reception timestamp of packet $p$.

This received-packet convention prevents lost packets from being assigned a nonexistent reception time. Packet delivery ratio should be reported separately when losses occur. The exact denominator convention of the paper should be checked before claiming an exact reproduction of its ADT calculation.

2.3 Experimental results

The paper compares satellite-based and terrestrial 5G configurations using ADT and demonstrates the use of moving satellite gNBs.

|Investigation               |Configuration                            |Main interpretation                                   |
|----------------------------|-----------------------------------------|------------------------------------------------------|
|Terrestrial versus satellite|Conventional gNB versus LEO satellite gNB|Satellite paths introduce additional propagation delay|
|User-count sweep            |1–6 UEs                                  |ADT can be compared across different user populations |
|Orbit geometry              |600 km altitude, minimum 20° elevation   |Slant range determines propagation delay              |
|Mobility                    |Two satellite gNBs                       |Handover is represented in the simulation             |
|Traffic profiles            |Two defined profiles                     |Simulator can distinguish service requirements        |

Propagation-delay estimate. For a link distance $d$ and speed of light $c$, the ideal one-way propagation time is:

$$
D_{\mathrm{propagation}} = \frac{d}{c}, \qquad c \approx 3.0\times 10^8\ \mathrm{m/s}.
$$

At a vertical distance of 600 km, this gives approximately 2 ms for one idealized one-way segment. The actual slant range is longer when the satellite is away from zenith. This estimate is not the same as full application-layer ADT.

Interpretation. The paper establishes a practical approach to defining satellite geometry, generating packets, and measuring delivery times. It is especially relevant to the experimental design of my project.

Caution: The exact numerical values plotted in the published ADT figure should be read from the full figure rather than inferred from this qualitative description.

2.4 Reproduction parameters

Scenario parameters reported in Table I:

|Parameter                  |Paper setting                                      |Status   |
|---------------------------|---------------------------------------------------|---------|
|Satellite gNBs             |2                                                  |Reported |
|Ground UEs                 |1–6                                                |Reported |
|Traffic profiles           |2                                                  |Reported |
|Satellite altitude         |600 km                                             |Reported |
|Orbit eccentricity         |0 (circular)                                       |Reported |
|Orbit inclination          |88°                                                |Reported |
|Argument of perigee        |90°                                                |Reported |
|Minimum elevation angle    |20°                                                |Reported |
|Packet size                |1280 bytes                                         |Reported |
|Packet count               |960                                                |Reported |
|Simulation time            |2 seconds                                          |Reported |
|Network technology         |ns-3-based 5G NR satellite-terrestrial model       |Reported |
|Carrier frequency          |Exact figure-specific setting not established here |To verify|
|Bandwidth and numerology   |Exact figure-specific settings not established here|To verify|
|MAC scheduler              |Exact scheduler setting not established here       |To verify|
|Packet inter-arrival model |Exact timing not established here                  |To verify|
|Random seeds / runs        |Exact values not established here                  |To verify|
|Simulator commit / revision|Exact version must be matched                      |To verify|

Reproduction procedure:

1. Configure two LEO satellite gNBs with the reported orbital parameters.
2. Create a remote host and 1–6 UEs.
3. Configure downlink packet flows with the reported packet size and count.
4. Enable the relevant satellite movement and handover mechanisms.
5. Run the 2-second scenario.
6. Record packet transmission and reception timestamps.
7. Calculate ADT for successfully delivered packets.
8. Compare satellite and terrestrial reference configurations.

Reproduction limitations. Matching the published results requires the original simulator implementation and its full PHY/MAC and traffic settings. The SNS3 API and satellite protocol model may differ, so the experiment should initially be used as a conceptual reference rather than a promise of exact numerical reproduction.

2.5 Implications for my project

1. Use a small satellite topology. Two satellites and a limited number of UEs are sufficient to motivate a manageable first scenario.
2. Define latency precisely. ADT provides a straightforward packet-timestamp-based metric.
3. Keep orbital geometry fixed in the initial load sweep. This isolates the effect of offered traffic.
4. Treat handover as an extension. It adds complexity and can be evaluated after the baseline works.
5. Verify SNS3 feature support before implementation. The paper’s simulator and SNS3 are different frameworks.

────────

3. Comparison

|Criterion                 |Paper 1: LEO Queuing Delay                     |Paper 2: 5G Satellite-Terrestrial Simulator|
|--------------------------|-----------------------------------------------|-------------------------------------------|
|Publication               |IEEE Access, 2021                              |IEEE MELECON, 2022                         |
|Main topic                |Queueing and time-varying satellite channels   |5G NTN system-level simulation             |
|Network                   |LEO constellation                              |LEO satellite gNBs and terrestrial UEs     |
|Method                    |Analytical queueing + C++ simulation           |ns-3-based simulation                      |
|Main varied inputs        |Traffic arrival rate, channel conditions       |UE count and scenario configuration        |
|Main metric               |Queueing and end-to-end delay                  |Average Delivery Time                      |
|Satellite mobility        |Simplified route snapshot for queueing analysis|Mobility and handover                      |
|Direct SNS3 implementation|No                                             |No                                         |
|Contribution to my project|Motivation for load-dependent delay            |Topology and packet-timestamp measurement  |

3.1 Common findings

Both papers demonstrate that satellite network performance cannot be characterized by propagation distance alone. The communication path, traffic demand, and network implementation affect measured delay.

3.2 Complementary findings

Paper 1 explains why packet queues and channel variability increase latency. Paper 2 demonstrates how a system-level 5G satellite scenario can be configured and measured. Together they motivate a controlled experiment in which traffic load changes while satellite geometry remains fixed.

3.3 Research gap

Neither paper evaluates precisely my proposed SNS3-based parameter sweep. My objective is therefore to establish a reproducible baseline experiment, not to claim that these papers have already validated the exact SNS3 configuration.

────────

4. Revised A1 Project Proposal

4.1 Original idea

Original title: QoS Performance Analysis of 5G Non-Terrestrial Networks Using ns-3.

The initial idea was to investigate satellite-network QoS, especially latency, using network simulation. The specific input parameters and the reproducible simulation scenario were not yet fully defined.

4.2 Revised title

Impact of Network Load on End-to-End Latency in LEO Satellite Networks Using SNS3

4.3 Research question

How does increasing network traffic load affect end-to-end packet latency in a LEO satellite communication scenario?

4.4 Changes and reasons

|Aspect           |A1 concept         |Revised after A3                   |Reason                                |
|-----------------|-------------------|-----------------------------------|--------------------------------------|
|Simulator        |General ns-3       |SNS3, after capability verification|Satellite-focused environment         |
|Scope            |Broad NTN QoS      |Load-dependent latency             |Specific, measurable research question|
|Geometry         |Not fixed          |Fixed LEO baseline                 |Isolate traffic effects               |
|Inputs           |Not fully specified|User count and offered rate        |Motivated by both papers              |
|Primary output   |General QoS        |Mean end-to-end latency            |Clear, reproducible metric            |
|Secondary outputs|Undecided          |Delay spread, 95th percentile, PDR |Capture variability and losses        |
|Experiment       |General simulation |Parameter sweep with repeated runs |Better reproducibility                |

Why the proposal changed. Paper 1 shows that traffic load and queues can strongly affect delay. Paper 2 provides an example of a satellite-network scenario and packet delivery measurement. I therefore narrowed my project to a controlled load–latency experiment, rather than changing many satellite and protocol parameters simultaneously.

Scope caveat: This revision is based on the A1 topic discussed during the project. The exact wording should be checked against the original A1 submission before final upload.

────────

5. Proposed SNS3 Experiment

> **Proposal only:** No simulation was run for A3. All values in this section are candidate settings and must be verified against a working SNS3 scenario.

5.1 Conceptual topology

flowchart LR
    U[Traffic sources / users] --> G[Ground terminal]
    G --> S[LEO satellite link]
    S --> R[Receiving terminal]
    R --> M[Latency measurements]

The satellite topology and channel settings will initially remain fixed.

5.2 Proposed input parameters

|Parameter            |Candidate values               |Purpose                                 |
|---------------------|-------------------------------|----------------------------------------|
|Active users         |1, 5, 10, 20                   |Change aggregate network load           |
|Offered rate per user|100 kbps, 500 kbps, 1 Mbps     |Change traffic intensity                |
|Satellite altitude   |600 km, if supported           |Fixed baseline motivated by Paper 2     |
|Transport            |UDP                            |Simple packet-level timing              |
|Packet size          |1000 bytes                     |Fixed traffic baseline                  |
|Traffic timing       |Constant rate initially        |Separate load from burstiness           |
|Simulation duration  |To be selected after validation|Enough packets for meaningful statistics|
|Random seeds         |Several documented runs        |Estimate run-to-run variability         |

A two-dimensional sweep across user count and offered rate would help distinguish the effects of the number of sources and their individual sending rates.

5.3 Output metrics

End-to-end delay per received packet:

$$
D_i = t_{\mathrm{RX},i} - t_{\mathrm{TX},i}
$$

Mean delay:

$$
\overline{D} = \frac{1}{N_{\mathrm{RX}}}\sum_{i=1}^{N_{\mathrm{RX}}}D_i
$$

Delay standard deviation:

$$
\sigma_D = \sqrt{\frac{1}{N_{\mathrm{RX}}}\sum_{i=1}^{N_{\mathrm{RX}}}(D_i-\overline{D})^2}
$$

Packet delivery ratio:

$$
PDR = \frac{N_{\mathrm{RX}}}{N_{\mathrm{TX}}}\times100%.
$$

The 95th-percentile delay can also be calculated from the sorted received-packet delays.

5.4 Planned procedure

1. Install a compatible SNS3 environment in a separate GitHub Codespace.
2. Build and run an existing satellite example without modifications.
3. Check which channel, topology, and traffic models are actually available.
4. Implement a small baseline topology.
5. Add UDP packet generation and timestamp-based latency measurement.
6. Confirm that packet counts and timestamps are correct.
7. Sweep the proposed user counts and offered traffic rates.
8. Repeat scenarios with documented random seeds.
9. Export measurements to CSV.
10. Plot mean latency, variability, and delivery ratio using Python.
11. Discuss whether the observed trends agree qualitatively with the literature.

5.5 Hypotheses

• H1: Mean latency will increase as offered load approaches link capacity.
• H2: Delay variability will increase under congestion.
• H3: With low offered load, propagation and transmission delay will dominate total latency.

These are hypotheses, not measured results.

────────

6. Limitations and Future Work

6.1 Literature limitations

The papers use different simulation frameworks and assumptions. Paper 1 is a queueing-oriented study, while Paper 2 is a 5G satellite-terrestrial system-level simulator. Their numerical results are not directly interchangeable. Some reproduction details, especially random seeds and selected PHY/MAC parameters, still need confirmation from the full experimental configuration.

6.2 Planned experiment limitations

• A small topology will not represent a complete operational constellation.
• Fixed satellite geometry will not capture all orbital mobility effects.
• Simplified UDP traffic may not reflect realistic applications.
• SNS3 may not expose exactly the same 5G NR mechanisms as Paper 2.
• Average latency for received packets does not describe losses; PDR should be reported separately.
• Exact numerical reproduction is not guaranteed when the simulator or channel model differs.

6.3 Future extensions

After establishing the baseline, possible extensions include changing satellite altitude or elevation angle, adding bursty traffic, evaluating handover, measuring throughput and jitter, and comparing different application QoS requirements.

────────

7. References

[1] On the Queuing Delay of Time-Varying Channels in Low Earth Orbit Satellite Constellations, IEEE Access, 2021. DOI: 10.1109/ACCESS.2021.3089005. IEEE Xplore.

[2] NS-3-based 5G Satellite-Terrestrial Integrated Network Simulator, IEEE MELECON, 2022. DOI: 10.1109/MELECON53508.2022.9843098. IEEE Xplore.

────────

Conclusion

The first paper demonstrates the importance of traffic load, time-varying satellite links, and queueing delay. The second provides a system-level example of 5G satellite-terrestrial performance measurement. Together they motivate a focused experiment on the relationship between network load and end-to-end latency. The revised project will use SNS3 if the required topology and tracing capabilities are supported. The next stage is to validate the simulator and implement a reproducible baseline.

A3 is a literature review and experiment proposal; no new simulation is claimed.
