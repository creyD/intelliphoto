set terminal png transparent size 640,240
set size 1.0,1.0

set terminal png transparent size 640,480
set output 'lines_of_code_by_author.png'
set key left top
set yrange [0:]
set xdata time
set timefmt "%s"
set format x "%Y-%m-%d"
set grid y
set ylabel "Lines"
set xtics rotate
set bmargin 6
plot 'lines_of_code_by_author.dat' using 1:2 title "Conrad" w lines, 'lines_of_code_by_author.dat' using 1:3 title "Sonaion" w lines, 'lines_of_code_by_author.dat' using 1:4 title "Jan Schuffenhauer" w lines, 'lines_of_code_by_author.dat' using 1:5 title "Jonas Mucke" w lines, 'lines_of_code_by_author.dat' using 1:6 title "AshBastian" w lines, 'lines_of_code_by_author.dat' using 1:7 title "Paul Norberger" w lines, 'lines_of_code_by_author.dat' using 1:8 title "Mienek" w lines, 'lines_of_code_by_author.dat' using 1:9 title "Bastian Schindler" w lines, 'lines_of_code_by_author.dat' using 1:10 title "Conrad Großer" w lines, 'lines_of_code_by_author.dat' using 1:11 title "deranonymos" w lines, 'lines_of_code_by_author.dat' using 1:12 title "DER Seb" w lines
