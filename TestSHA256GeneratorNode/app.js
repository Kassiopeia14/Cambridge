'use strict';

const readline = require('readline');
const rl = readline.createInterface({ input: process.stdin, output: process.stdout });

let sha256GeneratorModule = require('../modSHA256GeneratorWrap/build/Release/sha256Generator.node');
let SHA256GeneratorClass = sha256GeneratorModule.SHA256Generator;
const sha256Generator1 = new SHA256GeneratorClass();
const sha256Generator2 = new SHA256GeneratorClass();


let str = "Hello, Node!";

let result = sha256Generator1.generate(str);
console.log(str + "  =  " + result);

sha256Generator2.generate(str, (res) => {
    console.log(str + "  =  " + res);
});

//================================ Wait for User response =====================================
/*
rl.question('Press [Y] to continue: ', ans => {
    if (ans == 'y') console.log('i will continue')
    else console.log('i will not continue');
    rl.close();
});*/