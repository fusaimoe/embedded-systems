<h2>Consegna #4 - Event Tracker</h2>

Si vuole realizzare un sistema che permetta di fare il tracciamento nel tempo dei valori acquisiti con sensori e la gestione di situazioni di allarme come segue.

Il sistema deve essere composto da:

<ul>
    <li>sottosistema S1 su Raspberry Pi, che funge da centralina</li>
    <ul>
        <li>Led verde L1</li>
        <li>Led verde L2</li>
        <li>Led rosso L3</li>
        <li>Pulsante tattile T1</li>
    </ul>
    <li>sottosistema S2 su Arduino, con trasduttori</li>
    <ul>
        <li>sensore temperatura (analogico o digitale)</li>
        <li>rilevatore di movimento PIR</li>
        <li>dispositivo di attuazione a scelta A</li>
        <li>dispositivo Bluetooth</li>
    </ul>
    <li>sottosistema S3 su Android</li>
</ul>

I sistemi S1 e S2 sono collegati via seriale (asincrona, UART), mentre i sistemi S2 e S3 comunicano via Bluetooth.

<h4>Funzionalità del sistema</h4>

Il sistema deve:

<ul>
    <li>Tracciare  l’andamento della temperatura considerando campionamenti con un certo periodo P e gli eventi significativi relativi alle presenze rilevate (alle ore XX rilevata presenza, alle ore YY segnalato allarme (per l’allarme: vedere punto in seguito))</li>
    <li>Rendere accessibili/consultabili i dati rilevati in un modo a scelta dello studente. Esempi:</li>
    <ul>
        <li>via programma in esecuzione su S1, supponendolo dotato di un display touchscreen</li>
        <li>via web, installando su S1 un server web</li>
        <li>via server TCP o servizio web su HTTP</li>
    </ul>
    <li>Quando viene rilevata la presenza di qualcuno, sul sistema S3 deve essere richiesto se notificare o meno una situazione di allarme. In caso affermativo, deve essere acceso L3 e attivato il dispositivo di attuazione A. L’allarme può essere disattivato solo premendo il pulsante tattile T1, che riporta il sistema al normale funzionamento. La conferma o meno deve arrivare entro 10 secondi, passati i quali viene considerata una situazione di allarme.</li>
    <li>Il led L1 deve essere acceso ad indicare che  il sistema è in funzione. Mentre il led L2 deve lampeggiare ogni volta che avviene una comunicazione fra S1 e S2</li>
</ul>

<hr>

Per tutti gli aspetti non specificati, fare le scelte che si credono più opportune.
