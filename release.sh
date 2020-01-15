# Run CPP Check
echo "Running CPPCheck..."
cppcheck --enable=all --output-file=cppcheck_errors.txt src/
echo "CPPCheck finished"
# Uncrustify Files
echo "Running Uncrustify..."
find . \( -name "*.cpp" -o -name "*.c" -o -name "*.h" \) -exec uncrustify -c conf/uncrustify.cfg --no-backup {}
echo "Uncrustify finished."
# Run Unit Tests

# Remove Overhead Folders/ Files
echo "Cleaning directory..."
rm -r src/build-*
rm -r build-*/
rm -r Examples/
rm src/IntelliPhoto.pro.user
echo "Directory cleaned."
# Run Doxygen
echo "Running Doxygen..."
doxygen conf/intelliphoto_dox
echo "Doxygen finished."
