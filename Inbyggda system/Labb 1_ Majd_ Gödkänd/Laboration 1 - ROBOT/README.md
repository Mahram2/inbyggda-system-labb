Av: Majd Mansour & Hagar Alyasaki

Syfte:
Roboten följer en linje och kör runt hinder med hjälp av zScheduler i kaulab-biblioteket.

Funktion vi använde:
Linjesensorer: styr vänster/höger motor för att följa linjen.
Ultraljudssensor: upptäcker hinder närmare än SAFE_DIST (18 cm).
Hinderläge: Svänger bort från hindret och söker tillbaka till linjen.

Struktur
lineTask() linjeföljning och hinderkontroll
obstacleTask() rörelse runt hinder
drive() styr motorer
setup() initiering och schemaläggning

Användning
Installera biblioteken: kaulab, makeblockdrive, freertos.
Ladda upp koden via Arduino IDE.
Placera roboten på banan och starta.

// Använde AI som språkligt stöd för att rätta grammatiken i README texten.  
// Allt innehåll är dock eget och utgör ett självständigt arbete.