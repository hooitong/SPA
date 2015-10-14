echo off
cls
echo "Start Test"
start "" ..\..\EmptyGeneralTesting\Debug\AutoTester.exe FinalSource.txt QueryMerged.txt QueryMerged.xml

echo "Done: Check Result at QueryMerged.xml"