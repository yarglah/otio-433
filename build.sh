
rm ./otio_test
gcc OTIO.cpp OTIO_test.cpp ../rcswitch-pi/RCSwitch.cpp -l wiringPi -I ../rcswitch-pi/ -o otio_test
