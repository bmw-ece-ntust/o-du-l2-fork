# Refactor function

Start Date: 2024/05/06
Summary: Refactor the UL_TTI and DL_TTI request functions for improved code clarity and integration.
Status: Done
Assign: Ming 咚咚 [銘鴻], 陳奕全
Tags: Robert Task

UL_TTI.request and DL_TTI.request: avoid big switch, make cp functions for "sub"PDUs (PRACH, ...) -> indicate Robert to integrate in nfapi-fixes

- UL_TTI.request
    
    [UL_tti sub PDU](UL_tti%20sub%20PDU%2012110098314381d5ad30fb9ea8e4505d.md) 
    
- DL_TTI.request
    
    [DL_tti sub PDU](DL_tti%20sub%20PDU%201211009831438100adeecc481b61525d.md) 
    

[Revert "Slow down RFsim a bit for FAPI" (93d6984f) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/93d6984fc18828045841c197d9a6fa94498db041)

[Refactor DL TTI request handling and improve code clarity (dff187c6) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/dff187c6c822529903f595f920a83e06d9da00c4)

[Refactor UL TTI request handling and add clarity to function logic (56e5c957) · Commits · oai / openairinterface5G · GitLab](https://gitlab.eurecom.fr/oai/openairinterface5g/-/commit/56e5c9576714ca072facaa4876e498e4c2fea9b5)