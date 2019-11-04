# Softwareengineering - Übung 2

## Klassen
- Bild
  - Nutzt die Klasse "Farbe" zum übersetzen der Bytes in Farben
- RasterImage (Bild)
- ShapedImage (RasterImage)
- Tool
  - Wird auf Bild angewandt und verändert Pixel
  - Nutzen teilweise die Klasse "Farbe" zum verändern von Pixeln
- Drehen (Tool)
- Vergrößern/ Verkleinern (Tool)
- Setzen von Farbwerten (Tool)
- Zusammenfügen von Bildern (Tool)
- Tool History
  - Liste aus Tool Instanzen
- Farbe
  - Custom Model zur Speicherung der Farben
  - Konvertierung anderer Farbmodelle in den des Editors

## Verantwortlichkeiten
- Bild
  - Speichern
  - Laden
  - Anzeigen von Farben
- Tool
  - Verändern von Pixeln im Bild
  - Verändern von Farbwerten im Bild
- Farbe
  - Anzeigen auf dem Bildschirm
