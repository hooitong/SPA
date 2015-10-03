echo off
cls
echo "Start Test"
start "" ..\..\EmptyGeneralTesting\Debug\AutoTester.exe Advance_Source1.txt QuerySimplestTestCase.txt QuerySimplestTestCase.xml

echo "Done: Check Result at QueryMerged.xml"