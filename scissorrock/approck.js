let scis = document.querySelectorAll('.scissor')
let rock = document.querySelectorAll('.rock')
let pap = document.querySelectorAll('.paper')
let ps = document.getElementById('playerscore')
let cs = document.getElementById('computerscore')
let button = document.getElementById('play')
const choice = ['rock','paper','scissor'];
let playerchoice;
let computerchoice;

let playerwin = 0;
let computerwin = 0;

function computer(arr) {
    let randomchoice = Math.floor(Math.random() * arr.length);
    return arr[randomchoice];
   }

function count() {
    ps.textContent = playerwin;
    cs.textContent = computerwin;
}

scis.forEach((scissor) => {
    scissor.addEventListener("click", () => {
        playerchoice = 'scissor';
        computerchoice =  computer(choice);
        gamewincheck(playerchoice,computerchoice);
        count();
    } );
});

rock.forEach((rock) => {
    rock.addEventListener("click", () => {
        playerchoice = 'rock';
        computerchoice =  computer(choice);
        gamewincheck(playerchoice,computerchoice);
        count();

    } );
});

pap.forEach((paper) => {
    paper.addEventListener("click", () => {
        playerchoice = 'paper';
        computerchoice =  computer(choice);
        gamewincheck(playerchoice,computerchoice);
        count();

    } );
});

const playerwintext = 'Congrats You won';
const computerwintext = 'Sorry You lost, Computer wins.';


// /* Compare the Choices: Compare the computer's choice to the player's choice. If the computer's choice is rock and players choice is scissor computer wins else player wins. */

function gamewincheck(playerchoice,computerchoice) {
    if (playerchoice === '') {
        console.log('no choice selected by user.');
    }
    if (playerchoice === computerchoice) {
        console.log('draw');
    } else if (
        (playerchoice === 'rock' && computerchoice === 'scissor') ||
        (playerchoice === 'scissor' && computerchoice === 'paper') ||
        (playerchoice === 'paper' && computerchoice === 'rock')
    ){
        console.log('player wins');
        playerwin += 1;
        console.log(playerwin);
        button.textContent = 'Player won, Computer lost';

    }
    else{
        console.log('computer wins');
        computerwin += 1;
        console.log(computerwin);
        button.textContent = 'Computer won,player lost';

    }

}
