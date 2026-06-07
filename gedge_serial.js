let port = null, writer = null, reader = null;

// Default logger to use
export let log = (msg, cls) => console.log(`[hw] ${msg}`);

// Allow JS extension to override logger if needed
export function setLogger(fn) {
    log = fn;
}

export async function connect() {
    try {
        port = await navigator.serial.requestPort();
        await port.open({ baudRate: 115200 });
        writer = port.writable.getWriter();

        const info = port.getInfo();
        const v = info.usbVendorId, p = info.usbProductId;
        const vh = v != null ? v.toString(16).padStart(4, '0') : '?';
        const ph = p != null ? p.toString(16).padStart(4, '0') : '?';

        log(`[connect] Open @ 115200 baud (USB ${vh}:${ph})`, "ok");
        readLoop();
    } catch (e) {
        log(`[connect] Failed: ${e.message}`, "err");
    }
}

export async function disconnect() {
    try {
        if (reader) { await reader.cancel(); reader = null; }
        if (writer) { writer.releaseLock(); writer = null; }
        if (port)   { await port.close(); port = null; }

        log("[disconnect] Closed.", "ok");
    } catch (e) {
        log(`[disconnect] Error: ${e.message}`, "err");
    }
}

export async function send(text) {
    if (!text || !writer) return;
    try {
        await writer.write(new TextEncoder().encode(text));
        log(`[send] TX: ${text}`);
    } catch (e) {
        log(`[send] Write failed: ${e.message}`, "err");
    }
}

async function readLoop() {
    const dec = new TextDecoder();
    reader = port.readable.getReader();

    try {
        while (true) {
            const { value, done } = await reader.read();
            if (done) break;
            if (value && value.length) log(`[read] RX: ${dec.decode(value)}`);
        }
    } catch (e) {
        log(`[read] Error: ${e.message}`, "err");
    } finally {
        if (reader) {
            try { reader.releaseLock(); } catch (_) {}
        }
    }
}
