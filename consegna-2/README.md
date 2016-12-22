<h2>Consegna #2 - Smart Toilet</h2>

Si vuole realizzare un sistema embedded che implementi un ambiente che simuli una toilette intelligente.

<h4>Componenti HW</h4>

    2 led verdi (L1, L2) verdi + 1 led rosso (L3)
    2 pulsanti tattili (T1, T2)
    1 PIR
    1 sensore prossimità ad ultrasuoni

<h4>Comportamento del sistema</h4>

Si supponga di considerare come stato iniziale l’ambiente (toilette) vuoto, ovvero senza nessuna persona dentro.

Il sistema si presuppone percepisca la presenza di una persona entrata nella toilette mediante il sensore PIR.  Rilevata la presenza di una persona, il sistema deve accendere il led L1, che simula una luce. Finché il PIR rileva la presenza, la luce deve rimanere accesa. Quando il PIR non rileva più la presenza, dopo 10 secondi la luce deve spegnersi.

Il sistema è dotato di un sensore di prossimità con cui rileva la distanza della persona entrata dal WC. Quando questa distanza Dminwc scende sotto una certa soglia, si presuppone che la persona abbia iniziato ad usare il WC. A questo punto, quando la distanza aumenta sopra un certo valore Dmaxwc, si presuppone che la persona abbia finito di usare un WC e si accende il led L2 per 5 secondi con 4 pulsazioni al secondo (simula lo sciacquone). La presenza di un utente della toilette è rilevata anche nel caso in cui il PIR non rileva più la presenze,  tuttavia il sensore di prossimità rileva la persona entro la distanza Dmaxwc.

Dopo un certo numero nmaxutilizzi di utilizzi del WC, il sistema si presuppone entri in modalità di auto-pulizia/igienizzazione, per cui viene acceso il led rosso L3 e per 10 secondi si presuppone che nessun utente possa entrare nell’ambiente. Nel caso il PIR o il sensore di prossimità rilevano qualcuno in questo frangente, deve essere inviato un messaggio al PC collegato in modo che visualizzi il messaggio in uscita “ ”.

Nel caso venga rilevata la presenza (via sensore di prossimità) di una persona nell’ambiente immobile per più di Tmax secondi, allora deve essere fatto lampeggiare il led L3 e deve essere inviato un messaggio di allarme al PC collegato, da visualizzare in uscita. L’allarme deve essere generato anche a fronte della pressione del pulsante T1, per più di 2 secondi. Lo stato di allarme cessa a fronte della pressione del pulsante T2.

Inoltre il sistema deve:

<ul>
<li>tracciare complessivamente il numero di persone nuser che hanno usato la toilette, per fare in modo che questa informazione sia disponibile a fronte di richieste che arrivano da un PC via Seriale.</li>
<li>rendere disponibile - sempre a richieste che si presuppone arrivino da un PC connesso via seriale  - lo stato della toilette, se libero o occupato o allarme.</li>
</ul>

<hr>

Realizzare il sistema su Arduino + PC collegati via seriale, implementando il programma su Arduino in C++ e il programma su PC in Java.  Utilizzare un approccio a task, con modello di comportamento basato su macchine a stati finiti sincrone.

Per i parametri, utilizzare valori che si ritengono sensati a partire da valutazioni empiriche. Per tutti gli aspetti non specificati, fare le scelte che si credono più opportune.
