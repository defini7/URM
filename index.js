const tapeElement = document.getElementById("tape")

class Tape {
  constructor() {
    this.data = []
  }

  extend(newSize) {
    if (newSize > this.data.length) {
      for (let i = this.data.length; i < newSize; i++) {
        this.data.push(0)

        const regElem = document.createElement("input")
        regElem.innerText = 0
        regElem.id = `reg-${i}`
        tapeElement.appendChild(regElem)
      }
    }
  }

  set(reg, value) {
    this.extend(reg)
    this.data[reg - 1] = value
    console.log(tapeElement.childNodes, reg)
    tapeElement.childNodes[reg - 1].innerText = value
  }

  get(reg) {
    this.extend(reg)
    return this.data[reg - 1]
  }

  size() {
    return this.data.length
  }
}

const tape = new Tape()

const INSTRUCTIONS = {
  "z": r => {
    tape.set(r, 0)
  },

  "s": r => {
    tape.set(r, tape.get(r) + 1)
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

  const op = opcode.toLowerCase()

  if (!INSTRUCTIONS[op])
    console.error(`Invalid opcode {opcode}`)

  return INSTRUCTIONS[op](...(args.map(a => parseInt(a))))
}

function parseCode(code) {
  const lines = code.split("\n").filter((line, _) => line.length != 0)

  let cursor = 0

  while (cursor < lines.length) {
    let newCursor = parseInstruction(lines[cursor])

    if (newCursor)
      cursor = newCursor
    else
      cursor++
  }
}

document.getElementById("execute").onclick = () => {
  parseCode(document.getElementById("code").value)
}

document.getElementById("add-reg").onclick = () => {
  tape.extend(tape.size() + 1)
}

// z _
// s _
// t _ _
// j _ _ _
