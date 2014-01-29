Netverksstruktur versjon 1.0 


klienter kobler til master 

klienter får et nummer (id?) etter rekkefølgen de tilkobler master

klienter sender beskjed om at de fortsatt er tilgjengelig med gjevne mellomrom - (UDP?)

master svarer - (TCP?)

klientene har en id som de sender med meldingen for å identifisere seg

alle har en kopi av en liste for hvilke fårespørsler som er kommet inn og hva som skal gjøres

hvis klientene blir borte rekonfigurerer master alle komandokøen og fortsetter som før 

hvis masteren dør tar en av klientene over og prosedyren starter på nytt




--FOR MASTER

Vi deffinerer en maskin som master

Master initialiserer en socket klientene kobler til

Master håndterer alle tilkoblingsforespørslene i en select loop som kjører i main

Vær av klientene sender en forespørsel til master, om å få koble til, til den socketen klienten har initialisert 

Alle forespørslene aksepteres og den tilkoblingen kjøres i en tråd 

All prosessering skjer i en annen/andre tråder

Bruker IPC protokoll for å komunisere mellom trådene


