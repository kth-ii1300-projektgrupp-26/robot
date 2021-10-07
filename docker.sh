#!/bin/bash
# Bygger i Docker och kopierar till roboten
docker start ev3
docker exec -t ev3 /home/compiler/robot/build.sh
docker stop ev3

echo ""
echo "Kopierar till /home/robot/bin/mailman-$(date --iso-8601):"
# https://stackoverflow.com/questions/4018503/is-there-a-date-time-format-that-does-not-have-spaces/4018531
scp -r bin/ robot@10.42.0.101:/home/robot/bin/$(date --iso-8601)