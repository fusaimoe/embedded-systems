# Consegna #3 - Smart Car

* [Testo Consegna](https://github.com/fusaimoe/sistemi-embedded/wiki/Consegna-%233---Smart-Car)

## Note aggiuntive

Il progetto è stato sviluppato considerando che il veicolo possa trovarsi in quattro stati
principali:

* **OFF**: il veicolo è spento e il guidatore, ancora a bordo, può scegliere di entrare in
modalità parcheggio o di riaccendere l’auto.
* **PARK**: il veicolo viene parcheggiato e la macchina non può riaccendersi fino
all’uscita dalla modalità parcheggio, il bottone ON presente sull’applicazione android
risulta perciò disabilitato.
* **ONSTOP**: la macchina viene accesa ma non è ancora in movimento. Il bottone
PARKING viene disabilitato, si presuppone infatti che l’auto debba spegnersi prima di
poter entrare in modalità parcheggio.
* **ONMOVE**: ad auto accesa l’accelerometro rileva un movimento del veicolo. In
questo stato entrambi i bottoni dell’applicazione sono disabilitati, la macchina non
può spegnersi o venir parcheggiata se si trova ancora in movimento.
In fase progettuale abbiamo deciso, soprattutto per facilitare i test, che al rilevamento del
movimento da parte dell’accelerometro su Android, si aspettino almeno 5 secondi prima di
inviare comunicare ad Arduino la fine del movimento, a causa dell’instabilità dei dati ricevuti
dal sensore.

Abbiamo inoltre deciso che l’attacco in caso di collisione venga terminato quando il valore
dello stesso raggiunge il massimo. Momento in cui, di conseguenza, viene nascosta
l’interfaccia per l’interazione dell’utente.

Durante lo sviluppo del progetto, ci siamo resi conto che una miglior scelta progettuale
sarebbe potuta essere quella di creare, su Arduino, delle classi rappresentative dei
componenti dell’applicazione Android (per esempio AppToggleButton e AppSlider), invece
che settare variabili condivise come abbiamo fatto nella classe DetectMessageTask.
Riteniamo che in questo modo si sarebbe potuto rendere il codice più leggibile e si
sarebbero mantenuti i due contesti, di Arduino e di Android, maggiormente separati e
avrebbe reso più immediata la sostituzione di un componente virtuale con uno fisico.
Il progetto si potrebbe inoltre migliorare facendo sì che alla chiusura dell’applicazione
android, si riporti il sistema allo stato OFF e si attivi la sleep mode su arduino.

Purtroppo non siamo riusciti a completare queste migliorie entro i termini della consegna per
imprevisti nei test in laboratorio. Per lo stesso motivo purtroppo non abbiamo
completamente implementato l’azionamento del servo.
