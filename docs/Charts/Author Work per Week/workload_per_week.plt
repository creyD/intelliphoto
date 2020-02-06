set title "Arbeitsladung pro Woche"

set style data histogram
set style fill solid border rgb "black"

set auto x
set yrange[0:*]
unset ytics
set xlabel "Kalenderwoche"
set ylabel "Änderungen"
set border 0

set xtics border nomirror out

plot 'output.dat' using 2:xtic(1) notitle, \
            '' using 3:xtic(1) notitle, \
            '' using 4:xtic(1) notitle, \
            '' using 5:xtic(1) notitle, \
            '' using 6:xtic(1) notitle, \
            '' using 7:xtic(1) notitle