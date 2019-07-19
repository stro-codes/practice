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
    document.getElementById('content').innerHTML = '<iframe src="newBlogPost.html" style="width:100%; height:600px"></iframe>';
    document.getElementById('content').style.display = 'initial';
}

function insertNewPost() {

}

function loadImages() {
    document.getElementById('main_page').style.display = 'none';
    document.getElementById('content').innerHTML = '<object type="text/html" data="images.html" style="width:100%;height:800px"></object>';
    document.getElementById('content').style.display = 'initial';
} 

var myPost = [
    {
        "Title": "Test Post",
        "Date": "07/15/19",
        "Body": "Testing."
    }
]


