printLine(){
  echo "$2$1 \033[0m"
}

gitReset(){
  printLine "This will discard all your uncommited changes and restore the last commit. Continue?" "\033[0;33m"
  read
  git reset --hard
  printLine "Git resetted." "\033[0;32m"
}

runCPPCheck(){
  printLine "Running CPPCheck..."
  cppcheck -q --enable=all --output-file=cppcheck_errors.txt src/ || { printLine "ERROR: cppcheck not found!" "\033[0;33m"; return; }
  cppcheck -q --check-config --output-file=cppcheck_config.txt src/ || { printLine "ERROR: cppcheck not found!" "\033[0;33m"; return; }
  printLine "CPPCheck finished" "\033[0;32m"
}

runUncrustify(){
  printLine "Running Uncrustify..."
  find . \( -name "*.cpp" -o -name "*.c" -o -name "*.h" \) -exec uncrustify -q -c conf/uncrustify.cfg --no-backup {} + || { printLine "ERROR: uncrusify not found!" "\033[0;33m"; return; }
  printLine "Uncrustify finished." "\033[0;32m"
}

cleanDir(){
  printLine "Cleaning directory..."
  rm -r src/build-*
  rm -r build-*/
  rm -r Examples/
  rm src/*.pro.user
  printLine "Directory cleaned." "\033[0;32m"
}

runDoxygen(){
  printLine "Running Doxygen..."
  doxygen conf/intelliphoto_dox || { printLine "ERROR: doxygen not found!" "\033[0;33m"; return; }
  printLine "Doxygen finished." "\033[0;32m"
}

gitCommit(){
  printLine "Committing Changes to Git..."
  git add '*' || { printLine "ERROR: git not found!" "\033[0;33m"; return; }
  git commit -m "Automated Release Preparation"
  printLine "Committed." "\033[0;32m"
}

prepareMerge(){
  printLine "Merge Preparation started..."
  runUncrustify
  runCPPCheck
  runDoxygen
  gitCommit
  printLine "Finished." "\033[0;32m"
  exit
}

prepareRelease(){
  printLine "Release Preparation started..."
  gitReset
  cleanDir
  runUncrustify
  runCPPCheck
  runDoxygen
  gitCommit
  printLine "Finished." "\033[0;32m"
  exit
}

echo "Merge/ Release Preparation for IntelliPhoto started."
while true; do
    read -p "Do you want to prepare a (m)erge or a (r)elease?" yn
    case $yn in
        [Mm]* ) prepareMerge;;
        [Rr]* ) prepareRelease;;
        * ) printLine "Please answer (m)erge or (r)elease.";;
    esac
done
