# Compte-rendu TP4

## C - Système mémoire presque parfait

On termine la simulation en '224802' cycles avec 8 sets, un degré 1 d'associativité, 4 mots par ligne de cache et un buffer de 8 mots de 32 bits.

### C1
Pour 256 sets, 16 mots par ligne, 4 niveau d'associativité et un tampon d'écriture postées de profondeur de 8 mots de 32 bits la simulation termine en '74502' cycles.
Avec un cache plus grand avec un degré d'associativité plus grand et un nombre de famille beaucoup plus grands, la simulation met donc 3 fois plus de temps à terminer.

### C2
*** proc at cycle 74502
- INSTRUCTIONS       = 56510
- CPI                = 1.31839
- CACHED READ RATE   = 0.26889
- UNCACHED READ RATE = 0.0074677
- WRITE RATE         = 0.125465
- IMISS RATE         = 0.000619359
- DMISS RATE         = 0.00138203
- IMISS COST         = 24.4857
- DMISS COST         = 24.9048
- UNC COST           = 6
- WRITE COST         = 0

Taux de MISS du Cache d'instructions est de 0,062%.
Taux de MISS du Cache de données est de 0,138%.
Le CPI est de 1,318.

Pour l'évolution au cours du temps on analyse le résultat de cette commande: 
'./simul.x -NCYCLES 74502 -STATS 100'

Cycle 19001:
ICACHE: 0.247%
DCACHE: 0.313%

Cycle 47101:
ICACHE: 0.095%
DCACHE: 0.175%

Le taux de MISS baisse au fur et à mesure du temps.

Pour une analyse plus précise des 1000 premiers cycles:
Cycle 100:
ICACHE: 20.0%
DCACHE: 50.0%

Cycle 200:
ICACHE: 19.231%
DCACHE: 33.333%

Cycle 300:
ICACHE: 14.035%
DCACHE: 15.385%

Cycle 600:
ICACHE: 7.595%
DCACHE: 7.404%

Cycle 1000:
ICACHE: 8.520%
DCACHE: 13.699%

Le taux de MISS baisse de façon explicite lors des 1000 premiers cycles.

On peut interpréter que la diminution du taux de MISS au fur et à mesure du temps est due aux accès mémoire qui sont de plus en plus espacés (accès à tab[i]).

### C3
Une fonction 'transition' sur l'instance pibus_mips32_xcache est appelée et met à jour des attributs d'instrumentation pour mesurer le CPI et les taux de miss.
Le CPI est mesuré en divisant le compteur de cycles par le compteur d'instructions.
Les taux de MISS sont calculés en divisant le compteur de miss par le compteur d'instructions.


## D - Système mémoire presque parfait

-ISETS 	-IWORDS 	-IWAYS 	-DSETS 	-DWORDS 	-DWAYS   Miss |    
256 	8 	        1 	    256 	16 	        4         |
64 	    8 	        1 	    256 	16 	        4         |
16 	    8 	        1 	    256 	16 	        4         |
4 	    8 	        1 	    256 	16 	        4         |
1 	    8 	        1 	    256 	16 	        4         |