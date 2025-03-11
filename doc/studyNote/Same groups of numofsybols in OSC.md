# Same groups of numofsybols in OSC

Start Date: 2024/10/01
Summary: Resolving the selection issue of the number of symbols in OSC to ensure correct group selection across different message transmissions.
Status: Not started
Assign: Ming 咚咚 [銘鴻]

There is currently issue where SIB1 is set to carry 4 groups of `number of symbols (SLIV)` for selection, but OSC always selects the first group regardless of the situation. However, in the case of OAI VNF+PNF, OAI dynamically selects the first group when transmitting SIB1 and the second group when transmitting RAR (MSG2). By the time it reaches MSG4, the first group needs to be selected again.