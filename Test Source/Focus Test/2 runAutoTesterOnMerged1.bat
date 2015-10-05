echo off
cls
echo "Start Test"
start "" ..\..\EmptyGeneralTesting\Debug\AutoTester.exe Advance_Source1.txt QueryMerged1.txt QueryMerged1.xml

echo "Done: Check Result at QueryMerged.xml"