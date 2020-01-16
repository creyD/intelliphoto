# Discarding local changes
echo "\033[0;33mThis will discard all your uncommited changes and restore the last commit. Continue?\033[0m"
read
git reset --hard
# Run CPP Check
echo "Running CPPCheck..."
cppcheck --enable=all --output-file=cppcheck_errors.txt src/
cppcheck --check-config --output-file=cppcheck_config.txt src/
echo "\033[0;32mCPPCheck finished\033[0m"
# Uncrustify Files
echo "Running Uncrustify..."
find . \( -name "*.cpp" -o -name "*.c" -o -name "*.h" \) -exec uncrustify -c conf/uncrustify.cfg --no-backup {} +
echo "\033[0;32mUncrustify finished.\033[0m"
# Remove Overhead Folders/ Files
echo "Cleaning directory..."
rm -r src/build-*
rm -r build-*/
rm -r Examples/
rm src/*.pro.user
echo "\033[0;32mDirectory cleaned.\033[0m"
# Run Doxygen
echo "Running Doxygen..."
doxygen conf/intelliphoto_dox
echo "\033[0;32mDoxygen finished.\033[0m"
# Adding changes to git
echo "Committing Changes to Git..."
git add '*'
git commit -m "Automated Release Preparation"
echo "\033[0;32mCommitted.\033[0m"
echo "\033[0;32mFinished.\033[0m"
