HW=$(grep -m1 "model name" /proc/cpuinfo)

if [ "$HW" = "model name : Intel Atom(R) x6211E Processor @ 1.30GHz" ]; then
    echo "+ CPU check passed, Intel Atom x6211E detected, checking further..." | tee -a "$LOGFILE"
    BOARD_REQ="Q7-EL-X6211E-24N0211E"

elif [ "$HW" = "model name : Intel Atom(R) x6414RE Processor @ 1.50GHz" ]; then
    echo "+ CPU check passed, Intel Atom x6414RE detected, checking further..." | tee -a "$LOGFILE"
    BOARD_REQ="Q7-EL-X6414RE-25N0211I"

else
    echo "+ CPU not detected, exiting now..." | tee -a "$LOGFILE"
    exit "${ERROR_INCOMPATIBLE_HARDWARE}"
fi

BOARD_TYPE=$(cut -d' ' -f3 < /sys/class/dmi/id/board_name)

if [ "$BOARD_TYPE" = "$BOARD_REQ" ]; then
    echo "+ Mainboard check passed, checking further..." | tee -a "$LOGFILE"
else
    echo "+ boardtype: ${BOARD_TYPE}" | tee -a "$LOGFILE"
    echo "+ Required boardtype: ${BOARD_REQ}" | tee -a "$LOGFILE"
    echo "+ Compatible mainboard not detected, exiting now..." | tee -a "$LOGFILE"
    exit "${ERROR_INCOMPATIBLE_HARDWARE}"
fi