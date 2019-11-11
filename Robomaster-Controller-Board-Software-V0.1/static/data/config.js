/**
 * Chart configuration
 */
// Chart animation configuration
Chart.defaults.global.animation.duration =  10;

// Draw straight line
Chart.defaults.global.elements.line.tension = 0;

// Chart title mapping
chartsAxesConfig = [
    {
        name: 'Battery Voltage',
        xlabel: 'time (sec)',
        ylabel: 'Voltage (V)'
    },
    {
        name: 'Super Capacitor Voltage',
        xlabel: 'time (sec)',
        ylabel: 'Voltage (V)'
    },
    {
        name: 'Battery Current Draw',
        xlabel: 'time (sec)',
        ylabel: 'Amp (A)'
    },
    {
        name: 'Power Distribution Board Temperature',
        xlabel: 'time (sec)',
        ylabel: 'Temp (Deg C)'
    },
    {
        name: 'Capacitor Boosting Status',
        xlabel: 'time (sec)',
        ylabel: 'Status'
    },
    {
        name: 'Distance sensor #1',
        xlabel: 'time (sec)',
        ylabel: 'Distance (mm)'
    },
    {
        name: 'Distance sensor #2',
        xlabel: 'time (sec)',
        ylabel: 'Distance (mm)'
    },
    {
        name: 'Distance sensor #3',
        xlabel: 'time (sec)',
        ylabel: 'Distance (mm)'
    },
    {
        name: 'Distance sensor #4',
        xlabel: 'time (sec)',
        ylabel: 'Distance (mm)'
    },
    {
        name: 'Distance sensor #5',
        xlabel: 'time (sec)',
        ylabel: 'Distance (mm)'
    },
    {
        name: 'Distance sensor #6',
        xlabel: 'time (sec)',
        ylabel: 'Distance (mm)'
    },
    {
        name: 'Left Claw Status',
        xlabel: 'time (sec)',
        ylabel: 'Status'
    },
    {
        name: 'Right Claw Status',
        xlabel: 'time (sec)',
        ylabel: 'Status'
    },
    {
        name: 'NA',
        xlabel: 'NA',
        ylabel: 'NA'
    },
    {
        name: 'NA',
        xlabel: 'NA',
        ylabel: 'NA'
    }
];