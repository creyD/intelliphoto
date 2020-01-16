printLine(){
  echo "$2$1 \033[0m"
}

resetGit(){
  printLine "This will discard all your uncommited changes and restore the last commit. Continue?" "\033[0;33m"
  read
  git reset --hard
  printLine "Git resetted." "\033[0;32m"
}

runCPPCheck(){
  printLine "Running CPPCheck..."
  cppcheck --enable=all --output-file=cppcheck_errors.txt src/
  cppcheck --check-config --output-file=cppcheck_config.txt src/
  printLine "CPPCheck finished" "\033[0;32m"
}

runUncrustify(){
  printLine "Running Uncrustify..."
  find . \( -name "*.cpp" -o -name "*.c" -o -name "*.h" \) -exec uncrustify -c conf/uncrustify.cfg --no-backup {} +
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
  doxygen conf/intelliphoto_dox
  printLine "Doxygen finished." "\033[0;32m"
}

gitCommit(){
  printLine "Committing Changes to Git..."
  git add '*'
  git commit -m "Automated Release Preparation"
  printLine "Committed." "\033[0;32m"
}

prepareMerge(){
  printLine "Merge Preparation started..."
  printLine "Finished." "\033[0;32m"
  exit
}

prepareRelease(){
  printLine "Release Preparation started..."
  printLine "Finished." "\033[0;32m"
  exit
}

echo "Merge/ Release Preparation for IntelliPhoto started."
while true; do
    read -p "Do you want to prepare a (m)erge or a (r)elease?" yn
    case $yn in
        [Mm]* ) prepareMerge;;
        [Rr]* ) prepareRelease;;
        * ) echo "Please answer (m)erge or (r)elease.";;
    esac
done
