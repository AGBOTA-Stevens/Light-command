#include <Arduino.h>
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>YoupiLight</title>
    <style>
        input {
            width: 100%;
        }
    </style>
</head>
<body>
    <header>
        <h1>YOUPILIGHT</h1>
        <nav>
            <ul>
                <li><a href="#reglages">Réglages</a></li>
                <li><a href="#commandes">Commandes</a></li>
            </ul>
        </nav>
    </header>
    <main>
        <section>
            <h2>Heure actuelle</h2>
            <p><span id="heure">---</span> : <span id="minute">---</span> : <span id="seconde"> ---</span></p>
        </section>
        <section>
            <h2>Réglages horaires</h2>
            <form id="config-form">
            <fieldset>
                <legend><strong>Allumage</strong></legend>
                <label for="on_heure">Heure</label><input type="number" id="on_heure" placeholder="Entrer l'heure ici ..." min="0" max="23" required><br>
                <label for="on_minute">Minute</label><input type="number" id="on_minute" placeholder="Entrer la minute ici ..." min="0" max="59" required><br>
                <label for="on_seconde">Seconde</label><input type="number" id="on_seconde" placeholder="Entrer la seconde ici ..." min="0" max="59" required>
            </fieldset>
            <fieldset>
                <legend><strong>Extinction</strong></legend>
                <label for="off_heure">Heure</label><input type="number" id="off_heure" placeholder="Entrer l'heure ici ..." min="0" max="23" required><br>
                <label for="off_minute">Minute</label><input type="number" id="off_minute" placeholder="Entrer la minute ici ..." min="0" max="59" required><br>
                <label for="off_seconde">Seconde</label><input type="number" id="off_seconde" placeholder="Entrer la seconde ici ..." min="0" max="59" required>
            </fieldset>
            <button type="submit" id="btn_reglage">Envoyer le réglage</button>
            </form>
        </section>
        <section>
            <h2>Commande de la lampe</h2>
            <article>
                <p>Etat de la lampe : <span id="etat_lampe"><strong>Eteinte</strong></span></p>
                <button id="on_lampe">Allumer</button>
                <button id="off_lampe" disabled>Eteindre</button>
            </article>
        </section>
    </main>
    <footer>
        <p>&copy; YoupiLight - 2025 - Tous droits réservés</p>
    </footer>
    <script>
        let heureEl = document.getElementById('heure');
let minuteEl = document.getElementById('minute');
let secondeEl = document.getElementById('seconde');
const url_time = "/time";
// ==== GESTION DE L'AFFICHAGE DE L'HEURE ====
// Fonction pour recevoir le temps du module RTC 
async function getTime(url) {
    try {
        const response = await fetch(url);
        if(!response.ok) {
            throw new Error (`Erreur lors de la récupération du temps : ${response.status}`);
        }
        const data  = await response.json();
        if (data) return data;
    } catch (err) {
        console.log("Erreur : ",err.message)
    }
}

// Fonction pour afficher le temps reçu
async function displayTime(data) {
    try {
        const dataObject = await data;
        if (dataObject) {
            let heure = dataObject.heure;
            let minute = dataObject.minute;
            let seconde = dataObject.seconde;
            // Injection des données 
            minuteEl.textContent = minute || "___";
            heureEl.textContent = heure || "___";
            secondeEl.textContent = seconde || "___";            
        }
    }catch (err) {
        console.log("Erreur d'affichage :" ,err.message);
    }
}

const time = getTime(url_time);
displayTime(time);
// ==== Fin de la section d'affichage du temps ====

    </script>
    <!--script src="time.js" ></script>
    <script src="commandes.js"></script>
    <script src="config.js"></script-->
</body>
</html>
)rawliteral";
