let va1 = new VertexArray([
	0, 0, 0, 1,
	2, 0, 1, 1,
	2, 2, 1, 0,
	0, 2, 0, 0], [2, 2], gl.STATIC_DRAW);

//       0   1        2     3       4
//tex = [BG, SPRITES, main, bright, tmpBlur]
let fboBase = new FrameBuffer(width, height, 2, 2);
let fboBlur = [new FrameBuffer(canvas.width, canvas.height, 1, 4), new FrameBuffer(canvas.width, canvas.height, 1, 3)];

let bBase = new BatchBase(2000, ()=>{
	shaderBright.bind();
	fboBase.bind();
	gl.clear(gl.COLOR_BUFFER_BIT);
});
let bParticule = new BatchParticule(2000, ()=>{
	shaderParticule.bind();
	fboBase.bind();
});

let dR = 0.01;
let dG = 0.025;
let dB = 0.03;
let d = 10;
const rnd = Math.random;
/*for (let i = 0 ; i < 1000 ; i++)
	new Particule(rnd()*d, rnd()*d, 2, rnd(), rnd(), rnd(), 0.8);
*/
const render = () => {
	R += dR;
	G += dG;
	B += dB;
	if (R>1 || R<0) dR*=-1;
	if (G>1 || G<0) dG*=-1;
	if (B>1 || B<0) dB*=-1;

	bBase.bind();
	bBase.begin();
	for (let pipe of Pipe.list) {
		if (Math.random()>0.95)
			pipe.push(Math.ceil(Math.random()*5));
		pipe.flow();
		pipe.draw(bBase);
	}
	for (let tile of Tile.list)
		tile.draw(bBase);

	if (mouse.tile) {
		bBase.drawQuad(mouse.tile.x*side, mouse.tile.y*side, mouse.tile.size*side, mouse.tile.size*side, 9, .999, .1, .2, .3);
	}
	if (mouse.tile && mouse.tile.anchor(mouse.px, mouse.py)) {
		bBase.drawQuad(mouse.px*pside, mouse.py*pside, pside, pside, 9, .999, .0, 1, .6);
	} else {
		bBase.drawQuad(mouse.px*pside, mouse.py*pside, pside, pside, 9, .999, .4, .6, .7);
	}
	bBase.flush();
	
	/*bParticule.bind();
	bParticule.begin();
	for (let particule of Particule.list) {
		//particule.update();
		particule.draw(bParticule);
	}
	bParticule.flush();*/
	
	for (let i = 0 ; i < 1 ; i++) {
		fboBlur[0].bind();
		shaderBlurH.bind();
		va1.draw();
		fboBlur[1].bind();
		shaderBlurV.bind();
		va1.draw();
	}

	unbindAllFbo();
	shaderTex.bind();
	va1.draw();
}

let loop;
const start = () => {
	gl.activeTexture(gl.TEXTURE0);
	gl.bindTexture(gl.TEXTURE_2D, textures["sprites"]);
	gl.activeTexture(gl.TEXTURE1);
	gl.bindTexture(gl.TEXTURE_2D, textures["bg"]);

	loop = setInterval(render, 35);
}

setTimeout(start, 100);
