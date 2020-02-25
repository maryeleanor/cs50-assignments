// tabs on menu page

function onTabClick (thisTab){
   let activeTabs = document.querySelectorAll('.active');

  // hide any active tab
  for(let i = 0; i < activeTabs.length ;i ++){
      activeTabs[i].classList.remove("active");
  }

  // activate new tab
  thisTab.target.className += ' active';
  document.getElementById(thisTab.target.href.split('#')[1]).className += ' active';

 return false;

}


// contact form submission
 function contact(){

    let name = document.querySelector('#name').value;

    if(name === ''){
        alert("Thank you for contacting us. We'll get back to you soon.")
    }
    else{
        alert("Thanks " + name +", We'll get back to you soon.");
    }

    document.getElementById('contactForm').reset();

}


// reservation form
function reserve(){

    let date = document.querySelector('#resDate').value;
    date = date.split('-');
    console.log(date);

    let month = date[1];
    let months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'June', 'July', 'Aug', 'Sept', 'Oct', 'Nov', 'Dec'];
    let day = date[2];

    for(let i = 0; i < months.length; i++){
        if(month == i) {
            month = months[i-1];
            console.log(month);
        }
    }
    if(date == ''){
        alert("Please enter a date for your reservation");
    }
    else{
        alert("Great! You're all set for "+ month + " " + day + ".");
    }

    document.getElementById('reserveForm').reset();

}
