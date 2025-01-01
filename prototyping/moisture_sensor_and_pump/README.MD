Moisture output tested data
air: ~3150
damp paper towel: ~2500
submerged in water: ~1300

Design requirement:

water when plant has been dry for three days.

implementation:
each day takes two snapshots of the moisture level for past three days
6 different values stored
1 2 3 4 5 6 for six keys for six snapshots

all set to maximum moisture level 1.15 initially (because Vref is 3.3V)
moisture level will be read on a scale of 0 to 3.3/2.

A loop that loops through and update the 6 values
for every two values (a day), average value of 6 values is calculated.
    if below a set threhold
        water
        reset all values to maximum
    if above a set threshold
        do nothing
when last set value was 6, next set value is 1
otherwise next set value is (last_set_value + 1)

requirement 
1. NVS storage library
2. Timer to take snapshots twice a day


