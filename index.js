let tape = new Map()

function setTapeValue(key, value) {
  tape.set(key, value)
  
  const maxRegNum = Math.max(tape.keys())

  for (let i = lastMax; i <= maxRegNum; i++) {
    
  }
}

const INSTRUCTIONS = {
  "z": r => {
    tape.set(r, 0)
  },

  "s": r => {
    if (tape.has(r))
      tape.set(r, tape.get(r) + 1)
    else
      tape.set(r, 1)
  },

  "t": (r1, r2) => {
    tape.set(r2, tape.get(r1))
  },

  "j": (r1, r2, line) => {
    if (r1 == r2)
      return line
  }
}

function parseInstruction(inst) {
  const [opcode, ...args] = inst.split(' ')

  if (!INSTRUCTIONS[opcode])
    console.error(`Invalid opcode {opcode}`)

  return INSTRUCTIONS[opcode](...args)
}

function parseCode(code) {
  const lines = code.split('\n').filter((line, _) => line.length != 0)

  let cursor = 0;

  while (cursor < lines.length) {
    let newCursor = parseInstruction(lines[cursor])

    if (newCursor)
      cursor = newCursor;
    else
      cursor++;
  }
}

const tapeElement = document.getElementById("tape")

document.getElementById("execute").onclick = () => {
  parseCode(document.getElementById("code").value)
}

for (let i = 0; i <= 10; i++) {
  const btn = document.createElement("button");
  btn.innerText = i;
  btn.id = `register-${i}`;

  tapeElement.appendChild(btn);
}

// z _
// s _
// t _ _
// j _ _ _
