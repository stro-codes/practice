var result = 0;
var arr = {};

function add(x) {
    var y = Number(x);
    if(y == NaN)
        document.getElementById('output').value = 'NaN';
    else {
        result = result + document.getElementById('output').value;
        document.getElementById('output').value = '';
    }
}

function clear() {
    document.getElementById('output').value = ' ';
}

function equals(x) {
    var y = Number(x);
    if(y = NaN)
        document.getElementById('output').value = 'NaN';
    else {
        result = result + document.getElementById('output').value;
        document.getElementById('output').value = result;
    }
}
