<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no">
    <title>Robot Control Dashboard</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <div class="dashboard">
        <header class="header">
            <h1>Nexus Control</h1>
            <div class="status-indicator">
                <span id="connection-dot" class="dot offline"></span>
                <span id="connection-text">Waiting...</span>
            </div>
        </header>

        <div class="main-controls">
            <!-- Left Side: Movement D-Pad -->
            <div class="dpad-container glass-panel">
                <h2>Movement</h2>
                <div class="dpad">
                    <button class="btn control-btn btn-up" data-cmd="F">&#9650;</button>
                    <div class="dpad-middle">
                        <button class="btn control-btn btn-left" data-cmd="L">&#9664;</button>
                        <button class="btn control-btn btn-center" data-cmd="S">&#9899;</button>
                        <button class="btn control-btn btn-right" data-cmd="R">&#9654;</button>
                    </div>
                    <button class="btn control-btn btn-down" data-cmd="B">&#9660;</button>
                </div>
            </div>

            <!-- Right Side: Forklift & Clamp -->
            <div class="arms-container glass-panel">
                <h2>Actuators</h2>
                <div class="actuator-group">
                    <h3>Forklift</h3>
                    <div class="btn-group">
                        <button class="btn action-btn" data-cmd="U">UP</button>
                        <button class="btn action-btn bg-red" data-cmd="D">DOWN</button>
                    </div>
                </div>

                <div class="actuator-group mt-4">
                    <h3>Clamp</h3>
                    <div class="btn-group">
                        <button class="btn action-btn bg-cyan" data-cmd="O">OPEN</button>
                        <button class="btn action-btn bg-purple" data-cmd="C">CLOSE</button>
                    </div>
                </div>
            </div>
        </div>

        <div class="config-panel glass-panel">
            <h2>Serial Configuration</h2>
            <div class="input-group">
                <label for="com-port">COM Port (e.g., COM5):</label>
                <input type="text" id="com-port" value="COM4" class="styled-input">
                <button id="save-port" class="btn primary-btn">Save</button>
            </div>
            <p class="help-text">Pair HC-05 to your PC via Bluetooth and find the COM Port assigned to it.</p>
        </div>
    </div>
    <script src="script.js"></script>
</body>
</html>
