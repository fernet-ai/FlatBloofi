# FlatBloofi
La repentina evoluzione tecnologica ha delineato la struttura di sistemi informatici sempre più complessi.
Il trend economico segue quelli che sono i modelli più all'avanguardia  sull' elaborazione, l'acqusizione e l'archiviazione dei dati. 
Quest'ultimi non vengono adoperati necessariamente in contesti differenti, anzi, quasi nelle totalità delle applicazioni hi-tech, risultano essere interconnessi 
tra loro. Basti pensare all' **IoT Internet of Things**, grazie agli oggetti connessi alla rete, si riesce in modo costante a generare una enorme mole di dati. 
Il fenomeno **"Big Data** è quindi diventato un argomento di interesse di molte aziende, le quali hanno posto l'attenzione sul come archiviarli ai fini di trarne 
il massimo profitto. Gestirli, però, è diventato sempre più complesso e costoso, naturale conseguenza è stata la nascita di ambienti cloud. Il paradigma del 
**Cloud Computing** si esplica su un'architettura distribuita; perciò è necessario che le comunicazioni tra nodi, tramite scambio di messaggi, siano più efficienti 
possibili. Questo è solo uno dei molteplici scenari in cui strutture dati di **Bloom Filters** giocano il proprio ruolo. Un Bloom Filter è una struttura dati 
probabilistica (Il motivo della sua natura "probabilistica" verrà spiegata in modo dettagliato nei capitoli successivi) che, pur occupando una piccola quantità 
di memoria, sa essere molto potente soprattutto nel risolvere la classe di problemi che rispondono alla domanda: *"l'elemento x appartiene all'insieme S?*
L'efficienza dei Bloom Filters sta nel cosiddetto *"riferimento indiretto"*: durante una query di ricerca, l'oggetto da trovare in un dato insieme non viene 
confrontato direttamente con gli elementi della collezione. Bensì viene fatta una verifica di appartenenza ad un' astrazione di quelli che potrebbero essere 
i dati contenuti nell'insieme. Questa semplificazione fa sì che la computazione non sia troppo onerosa e che i costi per immagazzinare le informazioni relativi
al funzionamento della query siano notevolmente ridotti. Ritornando nell'ambito distribuito, ora siamo in grado di immaginare un nodo all'opera durante un scambio
di informazioni con un altro nodo. Sappiamo quanto la distanza possa notevolmente aggravare le prestazioni delle comunicazioni remote; ogni nodo potrebbe non 
condividere l'intero set di informazioni, ma solamente la sua rappresentazione probabilistica, permettendo uno scambio di dati molto più veloce.
L'uso dei Bloom Filters non si limita a questo. Nel corso del tempo hanno avuto un'applicazione in molti altri campi. Nella Bioinformatica, la scienza che studia
le metodologie per la risoluzione di problemi biologici per mezzo di metodi informatici, i Bloom Filters vengono usati per il sequenziamento del DNA. Alcuni 
Antivirus sfruttano le potenzialità di questa struttura dati per riconoscere codice malevolo su una lista di file; vengono usati inoltre nella compressione dei 
file, nella crittografia, nel web caching e in moltre altre applicazioni. La piattaforma Medium utilizza i Bloom Filters per evitare di consigliare articoli che
un utente ha già letto in precedenza. Il browser Web Google Chrome li utilizza per identificare URL dannosi. Qualsiasi URL viene prima verificato con 
un Bloom Filter locale e solo se ha restituito un risultato positivo viene eseguito un controllo completo dell'URL.
E' straordinario come una semplice definizione di una struttura matematica possa avere ripercussioni su una miriade di sfaccettature della nostra vita quotidiana. 
La domanda che si pone questo elaborato è: *Quali sono i limiti dei Bloom Filters?* Quando il numero di Bloom Filters aumenta, una sbagliata agglomerazione di 
essi può portare al breakdown dell'intera struttura. Inoltre, rappresentare in un unico Bloom Filter troppe collezioni di informazioni non risulterebbe
anch'esso efficiente.  Se precedentemente il nostro focus si soffermava sul determintare se un elemento appartenesse ad una lista, ora dobbiamo porre 
l'attenzione su quali tra le possibili liste è più probabile che ci sia l'elemento in questione. Questo problema viene definito come 
*”The multidimensional Bloom filter problem”*(Adina Crainiceanu and Daniel Lemire. Bloofi: Multidimensional bloom filters. Information Systems, 54:311–324, 2015).  
Secondo D.Lemire, le possibili soluzioni sono tre.  Si propone per prima una soluzione di tipo naive (ingenua); la seconda prevede la costruzione di un albero 
in cui le foglie rappresentano i Bloom Filters da indicizzare, mentre la radice è il Bloom Filter che rappresenta tutti gli elementi nel sistema.
Questa soluzione è chiamata **Bloofi**, implementata in C dal collega Fabiano Priore in "CBloofi" 
(Studio, analisi ed implementazione in C di una struttura gerarchica di Bloom filters), 
traendone dei risultati interessanti da confrontare con quelli di questo elaborato. L'ultima soluzione è chiamata **Flat Bloofi**:
una nuova struttura che sfrutta il parallelismo bit a bit intrinseco dei processori a 64 bit. 
Un Flat Bloofi viene definito come un array di interi dove ogni cella raggruppa un insieme di 64 bit e, ogni i-esimo bit dell'intero j, 
rappresenta l'i-esimo bit del j-esimo Bloom Filter.
L' elaborato si baserà principalmente sullo sviluppo e sulla valutazione di quest' ultima alternativa. 
Il primo capitolo fornisce un' introduzione ai Bloom Filters, spiegandone le proprietà, le operazioni usuali ed esempi più tangibili della loro applicazioni.
Si mostra inoltre quali sono i problemi relativi a quest'ultimi e l'esigenza di implementare  \textit{Bloofi} come prima soluzione, 
descrivendo anche qui le operazioni classiche. Il secondo capitolo introduce la definizione del \textit{Flat Bloofi}, punto cardine dello studio in esame. 
Si analizza la sua composizione, le motivazioni dello sviluppo, le strutture dati che entrano in gioco, in che modo si effettua una ricerca di un elemento, 
un inserimento, cancellazione e aggiornamento di un Bloom Filter. Il Capitolo 3  vede un' implementazione Java degli algoritmi trattati in precedenza 
e successivamente una nostra implementazione C. Il Capitolo 4 si concentra sul tesing delle implementazioni e sulla effettiva efficienza, finendo per 
poi fare un confronto fra le due. Il testing prosegue comparando le prestazioni del Flat Bloofi e del Bloofi in C. Nel quinto capitolo si traggono le
conclusioni sui vantaggi e svantaggi messi in evidenza da Bloofi e Flat Bloofi. Nel sesto ed ultimo capitolo si propongono ulteriori ottimizzazioni 
e possibili sviluppi futuri.
