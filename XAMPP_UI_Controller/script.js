document.addEventListener('DOMContentLoaded', () => {
    const buttons = document.querySelectorAll('.btn[data-cmd]');
    const statusDot = document.getElementById('connection-dot');
    const statusText = document.getElementById('connection-text');
    const comInput = document.getElementById('com-port');
    
    // Check local storage for previously saved port
    const savedPort = localStorage.getItem('robotComPort');
    if (savedPort) comInput.value = savedPort;

    document.getElementById('save-port').addEventListener('click', () => {
        localStorage.setItem('robotComPort', comInput.value);
        alert('COM Port saved successfully!');
    });

    const setStatus = (isOnline) => {
        if (isOnline) {
            statusDot.className = 'dot online';
            statusText.textContent = 'Connected & Transmitting';
        } else {
            statusDot.className = 'dot offline';
            statusText.textContent = 'Error / Offline';
        }
    };

    const sendCommand = (cmd) => {
        if (!cmd) return;
        const port = comInput.value;
        const formData = new FormData();
        formData.append('cmd', cmd);
        formData.append('port', port);

        fetch('api.php', {
            method: 'POST',
            body: formData
        })
        .then(res => res.text())
        .then(data => {
            if (data.includes('SUCCESS')) {
                setStatus(true);
            } else {
                setStatus(false);
                console.error("Arduino Error:", data);
            }
        })
        .catch(err => {
            setStatus(false);
            console.error('Fetch error:', err);
        });
    };

    // Prevent context menu and default zooming on phones
    document.addEventListener('contextmenu', e => e.preventDefault());

    // Button event listeners (handle both mouse and touch)
    buttons.forEach(btn => {
        const startAction = (e) => {
            e.preventDefault();
            btn.classList.add('active');
            let cmd = btn.getAttribute('data-cmd');
            sendCommand(cmd);
        };

        const stopAction = (e) => {
            e.preventDefault();
            btn.classList.remove('active');
            
            // Send stop command based on what was released
            let originalCmd = btn.getAttribute('data-cmd');
            
            // If movement button released
            if (['F', 'B', 'L', 'R'].includes(originalCmd)) {
                sendCommand('S'); // Stop movement
            } 
            // If Forklift button released
            else if (['U', 'D'].includes(originalCmd)) {
                sendCommand('d'); // Stop Forklift
            }
            // Clamp does not auto-stop on release, it stays opened/closed
        };

        btn.addEventListener('touchstart', startAction, {passive: false});
        btn.addEventListener('touchend', stopAction);
        btn.addEventListener('mousedown', startAction);
        btn.addEventListener('mouseup', stopAction);
        btn.addEventListener('mouseleave', (e) => {
            if (btn.classList.contains('active')) {
                stopAction(e);
            }
        });
    });
});
