# Thesis proposal

Start Date: 2025/01/17
Summary: Development of a new 5G nFAPI mode for OSC DU High to enhance interoperability with OAI Layer 1 and improve vendor integration.
Status: padding
Assign: Ming 咚咚 [銘鴻]
Tags: PIN

![image.png](image%20100.png)

- View Mode

[Overleaf, Online LaTeX Editor](https://www.overleaf.com/read/vjnndxrrxpgg#149143)

- Edit Mode

[Overleaf, Online LaTeX Editor](https://www.overleaf.com/4182878699ckypdwsnsrps#eeda21)

**Thesis Proposal**

**Title:**
Development and Integration of an nFAPI Mode for OSC DU High: Bridging OSC DU High and OAI Layer 1

**Introduction:**

**Background:**
The rapid advancements in 5G and beyond necessitate robust, flexible, and interoperable solutions for network functions. The O-RAN Software Community (OSC) is an open-source initiative established in collaboration with the O-RAN Alliance and the Linux Foundation in 2019. Its mission is to develop open software for the Radio Access Network (RAN), aligning with the O-RAN Alliance's open architecture and specifications to facilitate industry deployment. The OSC operates under the Apache 2.0 license, promoting modular, intelligent, efficient, and agile disaggregated RAN solutions. However, challenges remain in achieving seamless interoperation between different platforms and modes, especially in areas like DU (Distributed Unit) High Layer functionality.

**Problem Statement:**
Currently, OSC DU High supports only the FAPI mode implemented via the Wireless Service Library (Wls_lib) for vendor integration and relies on FlexRAN to achieve split 6 functionality. This approach limits vendor diversity and presents interoperability challenges, especially with OpenAirInterface (OAI) Layer 1. Furthermore, discrepancies in dedicated message transmissions—such as Master Information Block (MIB), System Information Block (SIB), and Random Access (RA) 4-step procedures—hinder effective integration due to differences in message formats and configurations across specifications.

**Research Objectives:**

1. Develop a new 5G Network Functional Application Platform Interface (5G nFAPI) mode (via socket) for OSC DU High.
2. Enhance vendor diversity by enabling 5G nFAPI as an alternative to FAPI mode.
3. Address inconsistencies in dedicated message transmission (e.g., MIB, SIB, RA 4-step) between OSC DU High and OAI Layer 1.
4. (Advanced) Separate parameter configurations from source code to facilitate future vendor integrations.
5. (Advanced) Containerize OSC DU High for improved maintainability and operational stability.

**Significance:**
This research contributes to the OSC community by expanding interoperability and enhancing functionality, providing a foundation for integrating diverse vendor solutions with OAI Layer 1. The proposed developments will drive innovation in 5G networks and beyond, particularly for research and development environments.

**Literature Review:**

1. Existing literature on 5G DU architecture highlights the importance of modular and interoperable interfaces.
2. Studies on 5G nFAPI and FAPI modes underscore the limitations of current implementations in terms of flexibility and vendor support.
3. Recent research on OSC and OAI integration showcases the technical and operational barriers, particularly in the transmission of dedicated messages such as MIB and SIB.
4. Advanced topics in containerization and parameterization demonstrate the potential for scalable and maintainable solutions in network deployments.

**Research Questions:**

1. How can a 5G nFAPI mode for OSC DU High be developed to support OAI Layer 1 integration?
2. What modifications are required to address dedicated message transmission inconsistencies (e.g., MIB, SIB, RA 4-step)?
3. What are the technical and operational benefits of separating parameters from source code and containerizing OSC DU High?

**Methodology:**

**Research Design:**
The study adopts a design-and-implement approach, integrating experimental validation and iterative development.

**Data Collection and Analysis:**

- Analyze existing OSC DU High and OAI Layer 1 implementations.
- Develop a prototype of the 5G nFAPI socket mode.
- Conduct comparative tests for FAPI and 5G nFAPI modes.
- Evaluate dedicated message transmission (e.g., MIB, SIB, RA 4-step) and resolve inconsistencies through systematic debugging and tracing.

**Resources Needed:**

- Access to OSC and OAI repositories.
- Development environment for DU High and Layer 1 debugging.
- Testing and validation tools for 5G nFAPI integration.

**Timeline:**

1. Month 1–3: Conduct preliminary research and environment setup.
2. Month 4–6: Develop and test 5G nFAPI mode integration.
3. Month 7–9: Address dedicated message transmission issues and implement parameter separation.
4. Month 10–12: Containerize OSC DU High and finalize experimental results.
5. Month 13–14: Draft and submit the thesis.

**Expected Outcomes:**

1. A functional 5G nFAPI mode for OSC DU High.
2. Resolution of dedicated message transmission inconsistencies (e.g., MIB, SIB, RA 4-step) between OSC and OAI.
3. Enhanced flexibility and scalability for future vendor integrations.
4. Improved maintainability through containerization and parameter management.

**Limitations:**

- Potential delays due to the complexity of debugging and integration.
- Resource constraints in testing across diverse vendor environments.

**References:**

1. Relevant studies on 5G nFAPI and FAPI implementations.
2. Documentation from OSC and OAI communities.
3. Technical literature on containerization and parameter management in 5G networks.

---

This proposal outlines a comprehensive research plan to address existing gaps in OSC DU High functionality and its integration with OAI Layer 1, aligning with the broader objectives of the OSC community and advancing interoperability in 5G networks.

- [UE Segmentation fault after Generating RRCSetupComplete](UE%20Segmentation%20fault%20after%20Generating%20RRCSetupCom%2012110098314381d1adf3f719885a3bf8.md)
- [How to Fix OSC asn1c Issues](How%20to%20Fix%20OSC%20asn1c%20Issues%20176100983143804bb9f3fd6a511b919c.md)