# Metanoia Collaboration Blueprint

Start Date: 2025/01/08
Summary: Collaboration blueprint for the 5G gNB SOC chip open testing platform focused on pre-silicon validation and integration testing strategies.
Status: padding
Assign: Ming 咚咚 [銘鴻]

# 5G gNB SOC Chip Open Testing Platform Blueprint

## Pre-Silicon Validation Strategy

This blueprint outlines the validation approach for the 5G gNB SOC platform before the actual chip is ready, focusing on software verification and integration testing.

### System Architecture Overview

[https://viewer.diagrams.net/?border=0&tags=%7B%7D&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=nFAPI.drawio&page-id=tARdYb7vdc35ZUzRhSSO#Uhttps%3A%2F%2Fdrive.google.com%2Fuc%3Fid%3D1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts%26export%3Ddownload](https://viewer.diagrams.net/?border=0&tags=%7B%7D&lightbox=1&highlight=0000ff&edit=_blank&layers=1&nav=1&title=nFAPI.drawio&page-id=tARdYb7vdc35ZUzRhSSO#Uhttps%3A%2F%2Fdrive.google.com%2Fuc%3Fid%3D1iXXPESGsNy2uM2wCgplps3eCRtnXG8Ts%26export%3Ddownload)

- Split architecture implementation using OAI (OpenAirInterface)
- Separation of O-DU HIGH and O-DU LOW components
- Ethernet-based connectivity between components
- nFAPI interface implementation for component communication

### Testing Setup

- Machine 1: Running O-DU HIGH component
    - Primary processing unit for upper layer functions
    - Handles RRC, PDCP, and higher MAC functions
- Machine 2: Running O-DU LOW component (SOC)
    - Manages lower layer functions
    - Handles PHY layer processing

### Integration Points

- Ethernet connection between machines for data transfer
- nFAPI/FAPI protocol implementation for standardized interface
- Verification of message passing and timing requirements

### Validation

1. Validation using OAI UE + rfsim + O-DU LOW platform
    - Testing interoperability between components
    - Verifying protocol compliance
    - Performance assessment
2. Validation using L1 ASIC
    - Hardware integration testing
    - Interface compatibility verification
    - End-to-end system validation

### Validation Steps

1. Setup of testing environment
2. Implementation of nFAPI interface protocols
3. Configuration of Ethernet connectivity
4. Verification of message exchange between O-DU HIGH and LOW
5. Performance testing and optimization
6. Integration testing with O-CU components

### Expected Outcomes

- Validated software architecture
- Verified interface protocols
- Established baseline performance metrics
- Documented integration procedures

### Next Steps

- [ ]  Obtain Metanoia hardware equipment (FPGA and other O-DU Low testing environment)
- [ ]  Configure network parameters for both machines
- [ ]  Implement nFAPI message handlers
- [ ]  Develop testing scripts for validation
- [ ]  Document performance benchmarks
- [ ]  Prepare integration test cases

## Meeting minutes

[（2025/01/15）會議重點摘要](%EF%BC%882025%2001%2015%EF%BC%89%E6%9C%83%E8%AD%B0%E9%87%8D%E9%BB%9E%E6%91%98%E8%A6%81%2017c10098314380329f15d3ab71888a10.md)