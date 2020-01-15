# Run CPP Check
cppcheck --enable=all --output-file=cppcheck_errors.txt src/
# Uncrustify Files
find . \( -name "*.cpp" -o -name "*.c" -o -name "*.h" \) -exec uncrustify -c conf/uncrustify.cfg --no-backup {}
# Run Unit Tests

# Remove Overhead Folders/ Files
rm -r src/build-*
rm -r build-*/
rm -r Examples/
rm src/IntelliPhoto.pro.user

# Run Doxygen
doxygen conf/intelliphoto_dox
