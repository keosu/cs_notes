// use strict
(() => {
  // grab the canvas element, get the context for API access and 
  // preset some variables
  const excuteCanvasDownload = () => {
    console.time('canvas')
    var canvas = document.querySelector('canvas'),
      c = canvas.getContext('2d'),
      mouseX = 0,
      mouseY = 0,
      width = 700,
      height = 300,
      colour = 'hotpink',
      mousedown = false;

    // resize the canvas
    canvas.width = width;
    canvas.height = height;

    function draw() {
      if (mousedown) {
        // set the colour
        c.fillStyle = colour;
        // start a path and paint a circle of 20 pixels at the mouse position
        c.beginPath();
        c.arc(mouseX, mouseY, 10, 0, Math.PI * 2, true);
        c.closePath();
        c.fill();
      }
    }

    // get the mouse position on the canvas (some browser trickery involved)
    canvas.addEventListener('mousemove', function (event) {
      if (event.offsetX) {
        mouseX = event.offsetX;
        mouseY = event.offsetY;
      } else {
        mouseX = event.pageX - event.target.offsetLeft;
        mouseY = event.pageY - event.target.offsetTop;
      }
      // call the draw function
      draw();
    }, false);

    canvas.addEventListener('mousedown', function (event) {
      mousedown = true;
    }, false);
    canvas.addEventListener('mouseup', function (event) {
      mousedown = false;
    }, false);
    const eleDrag = document.getElementById('drag')
    eleDrag.addEventListener('click', function (params) {
      eleDrag.href = canvas.toDataURL()
    }, false)
    console.timeEnd('canvas')

  }
  const getElement = (selector) => {
    return document.querySelectorAll(selector)
  }
  const loadDialogEvent = () => {
    var updateButton = document.getElementById('updateDetails');
    var favDialog = document.getElementById('favDialog');
    var outputBox = document.getElementsByTagName('output')[0];
    var selectEl = document.getElementsByTagName('select')[0];
    var confirmBtn = document.getElementById('confirmBtn');

    // “Update details” button opens the <dialog> modally
    updateButton.addEventListener('click', function onOpen() {
      if (typeof favDialog.showModal === "function") {
        favDialog.showModal();
      } else {
        alert("The dialog API is not supported by this browser");
      }
    });
    // "Favorite animal" input sets the value of the submit button
    selectEl.addEventListener('change', function onSelect(e) {
      confirmBtn.value = selectEl.value;
    });
    // "Confirm" button of form triggers "close" on dialog because of [method="dialog"]
    favDialog.addEventListener('close', function onClose() {
      outputBox.value = favDialog.returnValue + " button clicked - " + (new Date()).toString();
    });
  }
  const getTagsAmount = () => {
    // methods 1 base on foreach
    const list = document.querySelectorAll('.aside>ol>li')
    // let total = 0
    // list.forEach((item) => {
    //   const innerText = item.innerText
    //   const nub = Number(innerText.match(/(\d+)/g)[0])
    //   total += nub
    // })
    // return total

    // 转为类数组对象 先转为数组对象 call apply 会立即调用 bind调用时才会使用（惰性） 
    const arr1 = Array.prototype.slice.call(list) // 浅拷贝
    const arr2 = [...list] // 结构
    const arr3 = Array.prototype.map.call(list, item => {
      // console.log('call item :', item);
    })
    const arr4 = Array.prototype.map.bind(list) // bind
    const total = arr1.map(item => {
      const innerText = item.innerText
      const nub = Number(innerText.match(/(\d+)/g)[0])
      return nub
    }).reduce((pre, cur) => pre + cur)
    return total
  }
  const element = getElement('input#fm-sms-login-id.fm-text')
  loadDialogEvent()
  excuteCanvasDownload()
  console.log('total tag amount :', getTagsAmount());
  console.log('element :', element);
  console.info('Document loaded successfully')
  console.warn('Document loaded warn')
  console.error('Document loaded fail')
  console.dir({
    id: 1,
    name: 'ww'
  })
  console.log({
    id: 1,
    name: 'ww'
  })
  console.log([
    {
      id: 1,
      name: 'ww'
    },
    {
      id: 2,
      name: 'ww'
    }])
  console.table([
    {
      id: 1,
      name: 'ww'
    },
    {
      id: 2,
      name: 'ww'
    }])
  // logger.info('Document loaded successfully');

})()