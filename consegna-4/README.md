# Consegna #4 - Event Tracker

* [Testo Consegna](https://github.com/fusaimoe/sistemi-embedded/wiki/Consegna-%234---Event-Tracker)

## Raspberry Pi Config
First install Node.js and then JSON Server
* :baby: [Beginner’s Guide to Installing Node.js on a Raspberry Pi](http://thisdavej.com/beginners-guide-to-installing-node-js-on-a-raspberry-pi/)
* :fire: [JSON Server](https://github.com/typicode/json-server)

Then clone the repository

      git clone https://github.com/fusaimoe/sistemi-embedded.git
    
Move to the correct directory

      cd ./sistemi-embedded/consegna-4/event_tracker_web
    
And start JSON Server

      json-server --watch db.json
      
## Java
To compile the java project

      sudo javac -classpath bin:/usr/share/java/RXTXcomm.jar:"/home/pi/Development/sistemi-embedded/consegna-4/event_tracker_raspberry/lib/*" -d bin src/*.java
      
To execute the java project

      java -cp bin:/usr/share/java/RXTXcomm.jar:"/home/pi/Development/sistemi-embedded/consegna-4/event_tracker_raspberry/lib/*" Main args


## Schema
![](https://github.com/fusaimoe/sistemi-embedded/blob/master/consegna-4/messages-schema.png?raw=true)
