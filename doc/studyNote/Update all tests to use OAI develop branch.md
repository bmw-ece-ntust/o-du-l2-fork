# Update all tests to use OAI develop branch

Start Date: 2025/02/22
Summary: Updating all tests to utilize the OAI develop branch and establishing a comprehensive OAI testing environment.
Status: In progress
Assign: Ming 咚咚 [銘鴻]

[](https://gitlab.eurecom.fr/oai/openairinterface5g/-/blob/develop/doc/nfapi.md?ref_type=heads)

Robert mentioned that my previous commits submitted at EURECOM in France have all been merged into the develop branch, and now the OAI gitlab develop branch supports nfapi mode. Therefore, he suggested that I should update to develop for testing and development to avoid many issues. So I will update all development environments to the OAI develop branch, currently the tag for `2025/02/22` is `#2025.w07`.

Additionally, I want to establish a complete OAI split2 and split6 testing environment as a golden sample → (OAI CU + OAI DU High + OAI Layer1 + OAI UE), here is the testing list:

- [x]  OAI split2 (OAI CU + OAI DU + OAI UE) → [OAI split2 (OAI CU + OAI DU + OAI UE)](OAI%20split2%20(OAI%20CU%20+%20OAI%20DU%20+%20OAI%20UE)%201a2100983143808a8c3fcc9cf136143e.md)
- [x]  OAI split6 (OAI VNF + OAI PNF + OAI UE) → [OAI split6 (OAI VNF+ nFAPI + OAI PNF + OAI UE)](OAI%20split6%20(OAI%20VNF+%20nFAPI%20+%20OAI%20PNF%20+%20OAI%20UE)%201a2100983143800db810f9d6e5ff856c.md)
- [x]  OAI split 2 and 6 (OAI CU + OAI DU High + OAI Layer1 + OAI UE) → [OAI split2&6 (OAI CU+ OAI DU High+ nFAPI + OAI Layer1 + OAI UE)](OAI%20split2&6%20(OAI%20CU+%20OAI%20DU%20High+%20nFAPI%20+%20OAI%20Lay%201a210098314380feac8ef2b589dd2dbd.md)
- [ ]  OAI CU + OSC DU High + OAI Layer1 + OAI UE → [split2&6 (OAI CU+ OSC DU High+ nFAPI + OAI Layer1 + OAI UE)](split2&6%20(OAI%20CU+%20OSC%20DU%20High+%20nFAPI%20+%20OAI%20Layer1%20%201a2100983143801bbd82dfdcf6a61f38.md)