// main.ts
const rawCanvas = document.getElementById('rawCanvas') as HTMLCanvasElement;
const edgeCanvas = document.getElementById('edgeCanvas') as HTMLCanvasElement;

const rawCtx = rawCanvas.getContext('2d')!;
const edgeCtx = edgeCanvas.getContext('2d')!;

let fps = 30;
let jniCalls = 0;
let framesReceived = 0;

// Draw Raw Camera Feed
function drawRawFeed(): void {
    rawCanvas.width = 640;
    rawCanvas.height = 480;

    const gradient = rawCtx.createLinearGradient(0, 0, rawCanvas.width, rawCanvas.height);
    gradient.addColorStop(0, '#667eea');
    gradient.addColorStop(0.5, '#764ba2');
    gradient.addColorStop(1, '#f093fb');

    rawCtx.fillStyle = gradient;
    rawCtx.fillRect(0, 0, rawCanvas.width, rawCanvas.height);

    rawCtx.fillStyle = 'rgba(255, 255, 255, 0.3)';
    rawCtx.beginPath();
    rawCtx.arc(200 + Math.sin(Date.now() / 1000) * 50, 240, 80, 0, Math.PI*2);
    rawCtx.fill();

    rawCtx.beginPath();
    rawCtx.arc(440 + Math.cos(Date.now() / 800) * 30, 240, 60, 0, Math.PI*2);
    rawCtx.fill();
}

// Draw Edge Detection Feed
function drawEdgeDetection(): void {
    edgeCanvas.width = 640;
    edgeCanvas.height = 480;

    edgeCtx.fillStyle = '#000';
    edgeCtx.fillRect(0,0, edgeCanvas.width, edgeCanvas.height);

    edgeCtx.strokeStyle = '#fff';
    edgeCtx.lineWidth = 2;

    edgeCtx.beginPath();
    edgeCtx.arc(200 + Math.sin(Date.now() / 1000) * 50, 240, 80, 0, Math.PI*2);
    edgeCtx.stroke();

    edgeCtx.beginPath();
    edgeCtx.arc(440 + Math.cos(Date.now() / 800) * 30, 240, 60, 0, Math.PI*2);
    edgeCtx.stroke();

    for(let i=0;i<100;i++){
        edgeCtx.beginPath();
        edgeCtx.arc(Math.random()*edgeCanvas.width, Math.random()*edgeCanvas.height, 1, 0, Math.PI*2);
        edgeCtx.fillStyle = 'rgba(255,255,255,0.5)';
        edgeCtx.fill();
    }
}

// Update stats
function updateStats(): void {
    fps = 25 + Math.random()*10;
    (document.getElementById('fpsDisplay') as HTMLElement).textContent = Math.round(fps).toString();
    (document.getElementById('frameTime') as HTMLElement).textContent = Math.round(1000/fps) + 'ms';
    (document.getElementById('rawFps') as HTMLElement).textContent = Math.round(fps) + ' FPS';
    (document.getElementById('edgeFps') as HTMLElement).textContent = Math.round(fps-2) + ' FPS';

    jniCalls += Math.floor(Math.random()*5);
    (document.getElementById('jniCalls') as HTMLElement).textContent = jniCalls.toString();

    framesReceived += Math.floor(Math.random()*3);
    (document.getElementById('framesReceived') as HTMLElement).textContent = framesReceived.toString();

    const procTime = 10 + Math.random()*5;
    (document.getElementById('procTime') as HTMLElement).textContent = procTime.toFixed(1) + 'ms';
}

// Toggle view buttons
function toggleView(view: string): void {
    const buttons = document.querySelectorAll('.toggle-buttons .btn-secondary');
    buttons.forEach(btn => btn.classList.remove('active'));
    (event?.target as HTMLElement)?.classList.add('active');
}

// Animation loop
function animate(): void {
    drawRawFeed();
    drawEdgeDetection();
    requestAnimationFrame(animate);
}

setInterval(updateStats, 1000);
animate();
