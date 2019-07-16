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

function loadHome() {
    document.getElementById('content').style.display = 'none';
    document.getElementById('content').innerHTML = '';
    document.getElementById('main_page').style.display = 'initial';
}

function loadAbout() {
    document.getElementById('main_page').style.display = 'none';
    document.getElementById('content').innerHTML = '<object type="text/html" data="about.html"></object>';
    document.getElementById('content').style.display = 'initial';
}

function addBlogPost() {
    document.getElementById('main_page').style.display = 'none';
    document.getElementById('content').innerHTML = '<object type="text/html" style="width:100%; height:100%" data="newBlogPost.html"></object>';
    document.getElementById('content').style.display = 'initial';
    document.getElementById('post_container').innerHTML = document.getElementById('post_container').innerHTML + ('<div class="w3-card-4 w3-margin w3-white"> <div class="w3-container w3-blue"><h2 class="post_header">Todays Header</h2> <h4 class="post_date">07/15/19</h4></div><form class="w3-container w3-padding w3-margin"><p>lorem ipsum lorem ipsum lorem ipsum lorem ipsum lorem ipsum lorem ipsum </p></form></div>');

}

function loadImages() {
    document.getElementById('main_page').style.display = 'none';
    document.getElementById('content').innerHTML = '<object type="text/html" data="images.html" style="width:100%;height:100%"></object>';
    document.getElementById('content').style.display = 'initial';
} 

var testObject = {
    name: "testy",
    age: 1,
    grades: [],
};

