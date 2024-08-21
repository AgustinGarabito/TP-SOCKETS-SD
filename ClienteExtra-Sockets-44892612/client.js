const net = require('net');
const readline = require('readline');

// CONFIG
const PORT = 5005;
const HOST = '127.0.0.1';

// CONSOLA
const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout
});

// CLIENTE TCP
const client = new net.Socket();

// CONEXION
client.connect(PORT, HOST, () => {
    console.log('Conectado al servidor.');
});

// RECIBIR DATOS
client.on('data', (data) => {
    console.log(`Mensaje recibido:\n${data.toString('utf8')}`);

    rl.question('\nIngrese el número de opción deseada: ', (input) => {
        client.write(input);
    });
});

// CERRAR CONEXION
client.on('close', () => {
    console.log('\n\n-----------------CONEXION CERRADA-----------------\n\n');
    process.exit();
});

// ERRORES
client.on('error', (err) => {
    console.error('Error:', err.message);
    process.exit(1);
});