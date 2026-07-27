#!/bin/bash

# 1. In den Magnetkran-Ordner wechseln
cd ~/Developer/Magnetkran || exit

# 2. Alle LibreOffice-Dateien (.odt, .ods, .odp, .odg, .odb, .odf) suchen 
# und direkt im jeweiligen Zielordner als PDF neu generieren/aktualisieren
find . -type f \( -name "*.odt" -o -name "*.ods" -o -name "*.odp" -o -name "*.odg" -o -name "*.odb" -o -name "*.odf" \) | while read -r FILE; do
    DIR=$(dirname "$FILE")
    libreoffice --headless --convert-to pdf "$FILE" --outdir "$DIR" 2>/dev/null
done

# 3. Datum und Uhrzeit holen
DATUM=$(date +"%d.%m.%Y - %H:%M Uhr")

# 4. Alle Dateien (inkl. der erzeugten PDFs und Skripte) vormerken
git add .

# 5. Nur committen und pushen, wenn es Änderungen gab
if ! git diff-index --quiet HEAD --; then
    git commit -m "Automatisches Backup vom $DATUM"
    git push origin main
    notify-send "Git Backup" "Magnetkran-Projekt & PDFs erfolgreich gesichert!" -i document-save
fi

# 6. Wieder ins Home-Verzeichnis zurückkehren
cd ~
