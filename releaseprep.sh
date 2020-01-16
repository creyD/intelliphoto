# Discarding local changes
echo "\033[0;33mThis will discard all your uncommited changes and restore the last commit. Continue?"
read
git reset --hard
# Run CPP Check
echo "Running CPPCheck..."
cppcheck --enable=all --output-file=cppcheck_errors.txt src/
cppcheck --check-config --output-file=cppcheck_config.txt src/
echo "\033[0;32mCPPCheck finished"
# Uncrustify Files
echo "Running Uncrustify..."
find . \( -name "*.cpp" -o -name "*.c" -o -name "*.h" \) -exec uncrustify -c conf/uncrustify.cfg --no-backup {} +
echo "\033[0;32mUncrustify finished."
# Remove Overhead Folders/ Files
echo "Cleaning directory..."
rm -r src/build-*
rm -r build-*/
rm -r Examples/
rm src/*.pro.user
echo "\033[0;32mDirectory cleaned."
# Run Doxygen
echo "Running Doxygen..."
doxygen conf/intelliphoto_dox
echo "\033[0;32mDoxygen finished."
# Adding changes to git
echo "Committing Changes to Git..."
git add '*'
git commit -m "Automated Release Preparation"
echo "\033[0;32mCommitted."
echo "\033[0;32mFinished."
