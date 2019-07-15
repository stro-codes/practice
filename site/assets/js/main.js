function myfuncor() {
    var x = document.getElementById('first').innerHTML;
    var y = document.getElementById('last').innerHTML;
    return result = "hello world!";
}

function findAndSwap() {
    // grab attributes for a node to be found
    var tag = document.getElementById('first').value;
    var classs = document.getElementById('last').value;
    var id = document.getElementById('id').value;

    // grab data from node that is found
    var x = document.getElementsByClassName('classs').getElementsByTagName('tag').getElementById('id').innerHTML;

    // display that text
    document.getElementById('test').value = x;
}

function fudge() {
    var tag = document.getElementById('first').value;
    var classs = document.getElementById('last').value;

    document.getElementById('a').innerHTML = tag;
    document.getElementById('b').innerHTML = classs;

    document.getElementById('cardAlert').style.visibility = 'visible';
}

function closeCardAlert() {
    document.getElementById('cardAlert').style.visibility = 'hidden';
}

var testObject = {
    name: "testy",
    age: 1,
    grades: [],
};

