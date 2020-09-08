FROM miracoli286/embedded-software-ci:v1.3
COPY . /usr/src/app

WORKDIR /usr/src/app
RUN g++ -O0 -fno-inline -fno-inline-small-functions -fno-default-inline --coverage -fprofile-arcs -ftest-coverage -Wold-style-cast -Wall -Weffc++ tst/FixedPointsTest.cpp -o FixedPointsTest -lboost_unit_test_framework -I src/
RUN ./FixedPointsTest

RUN mkdir coverage
RUN gcovr -r .  --exclude='.*Test.*' --html --html-details -o coverage/gcovr.html
RUN gcovr -r .  --exclude='.*Test.*'
RUN gcovr -b -r .  --exclude='.*Test.*'
CMD rm -rf /github/workspace/* && cp -r /usr/src/app/* /github/workspace/
