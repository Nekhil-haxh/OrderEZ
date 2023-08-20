const static char index_first[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Smart Cafe</title>
  <script src="https://cdn.jsdelivr.net/npm/vue@2.6.14/dist/vue.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/axios/0.21.1/axios.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/gsap/3.9.1/gsap.min.js"></script>
  <script type="module" src="https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.esm.js"></script>
  <script nomodule src="https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.js"></script>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.4/jquery.min.js"></script>
</head>
<body>
  <div class="wrapper">
    <div class="screen -left" id="shopItems">
        <div class="cart-icon" onclick="showCart()">
            <ion-icon name="cart" class="icon"></ion-icon>
        </div>
      <div class="app-bar">
      </div>
      <div class="title">Our items</div>
      <div class="shop-items">
      </div>
    </div>
    <div class="screen -right" id="cartItems">
        <div class="cart-icon" onclick="hideCart()">
            <ion-icon name="cart" class="icon"></ion-icon>
        </div>
      <div class="app-bar">
      </div>
      <div class="title">Picked Items</div>
      <div class="no-content" v-if="cartItems.length === 0">
      </div>
      <div class="cart-items">
      </div>
      <div id="checkoutButtonContainer">
      </div>
      <form id="checkoutForm" action="http://192.168.1.7/order" method="POST">
        <input type="hidden" name="cartItems" id="cartItemsInput">
    </form>
    </div>
  </div>
)=====";


const static char index_sec[] PROGMEM = R"=====(
<style>
    body {
  font-family: "Rubik", sans-serif;
  color: #303841;
  overflow: hidden;
}
.wrapper {
  height: 100vh;
  display: flex;
  align-items: center;
  justify-content: space-between;
  position: relative;
  flex-wrap: wrap;
  padding: 40px 20px;
  max-width: 720px;
  margin: 0 auto;
}
.wrapper::before {
  content: "";
  display: block;
  position: fixed;
  width: 300%;
  height: 100%;
  top: 50%;
  left: 50%;
  border-radius: 100%;
  transform: translateX(-50%) skewY(-8deg);
  background-color: #f6c90e;
  z-index: -1;
  animation: wave 8s ease-in-out infinite alternate;
}
@keyframes wave {
  0% {
    transform: translateX(-50%) skew(0deg, -8deg);
  }
  100% {
    transform: translateX(-30%) skew(8deg, -4deg);
  }
}

@media(max-width:700px) {
.screen {
    background-color: #fff;
    box-sizing: border-box;
    width: 340px;
    height: 600px;
    box-shadow: 0 3.2px 2.2px rgba(0, 0, 0, 0.02), 0 7px 5.4px rgba(0, 0, 0, 0.028), 0 12.1px 10.1px rgba(0, 0, 0, 0.035), 0 19.8px 18.1px rgba(0, 0, 0, 0.042), 0 34.7px 33.8px rgba(0, 0, 0, 0.05), 0 81px 81px rgba(0, 0, 0, 0.07);
    border-radius: 30px;
    overflow-y: scroll;
    padding: 0 28px;
    position: relative;
    margin-bottom: 20px;
    margin-left: 10%;
    }
.cart-icon{
    width: 3.5rem;
    height: 2.9rem;
    position: fixed;
    margin-left: 12rem;
    margin-top: -8.5rem;
    z-index: 0;
    background-color: #f6c90e;
    border-radius: 0.4rem 0.4rem 0 0;
    cursor: pointer;
}
.cart-icon .icon{
    width: 2rem;
    height: 2rem;
    margin-left: 0.5rem;
    margin-top: 0.3rem;
    cursor: pointer;
    z-index: 0;
    
}
#cartItems{
    display: none;
}
}
@media (min-width: 781px) {
    .screen {
    background-color: #fff;
    box-sizing: border-box;
    width: 340px;
    height: 600px;
    box-shadow: 0 3.2px 2.2px rgba(0, 0, 0, 0.02), 0 7px 5.4px rgba(0, 0, 0, 0.028), 0 12.1px 10.1px rgba(0, 0, 0, 0.035), 0 19.8px 18.1px rgba(0, 0, 0, 0.042), 0 34.7px 33.8px rgba(0, 0, 0, 0.05), 0 81px 81px rgba(0, 0, 0, 0.07);
    border-radius: 30px;
    overflow-y: scroll;
    padding: 0 28px;
    position: relative;
    margin-bottom: 20px;
    }
    .cart-icon{
        display: none;
    }
}

.screen::before {
  content: "";
  display: block;
  position: absolute;
  width: 300px;
  height: 300px;
  border-radius: 100%;
  background-color: #f6c90e;
  top: -20%;
  left: -50%;
  z-index: 0;
}
.screen::-webkit-scrollbar {
  display: none;
}
.screen > .title {
  font-size: 24px;
  font-weight: bold;
  margin: 20px 0;
  position: relative;
}
.app-bar {
  padding: 12px 0;
  position: relative;
}
.app-bar > .logo {
  display: block;
  width: 50px;
}
.shop-items {
  position: relative;
}
.item-block {
  padding: 40px 0 70px;
}
.item-block:first-child {
  padding-top: 0;
}
.item-block > .image-area {
  border-radius: 30px;
  height: 380px;
  display: flex;
  align-items: center;
  overflow: hidden;
}
.item-block > .image-area > .image {
  display: block;
  width: 100%;
  filter: drop-shadow(0 30px 20px rgba(0, 0, 0, 0.2));
}
.item-block > .name {
  font-size: 20px;
  font-weight: bold;
  margin: 26px 0 20px;
  line-height: 1.5;
}
.item-block > .description {
  font-size: 13px;
  color: #777;
  line-height: 1.8;
  margin-bottom: 20px;
}
.item-block > .bottom-area {
  display: flex;
  justify-content: space-between;
  align-items: center;
}
.item-block > .bottom-area > .price {
  font-size: 18px;
  font-weight: bold;
}
.item-block > .bottom-area > .button {
  cursor: pointer;
  background-color: #f6c90e;
  font-weight: bold;
  font-size: 14px;
  box-sizing: border-box;
  height: 46px;
  padding: 16px 20px;
  border-radius: 100px;
  box-shadow: 0 3px 6px rgba(0, 0, 0, 0.2);
  transition: box-shadow 0.4s, background-color 0.2s;
  user-select: none;
  white-space: nowrap;
  position: relative;
  display: flex;
  align-items: center;
  overflow: hidden;
}
.item-block > .bottom-area > .button:hover {
  background-color: #f8d43f;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.15);
}
.item-block > .bottom-area > .button.-active {
  pointer-events: none;
  cursor: default;
}
.item-block > .bottom-area > .button > .cover {
  width: 16px;
  height: 16px;
  position: absolute;
  display: flex;
  justify-content: center;
  align-items: center;
}
.item-block > .bottom-area > .button > .cover > .check {
  width: 100%;
  height: 100%;
  transform: translate(-100%, -73%) rotate(-45deg);
  position: absolute;
  left: 50%;
  top: 50%;
}
.item-block > .bottom-area > .button > .cover > .check::before, .item-block > .bottom-area > .button > .cover > .check::after {
  content: "";
  display: block;
  background-color: #303841;
  position: absolute;
  left: 0;
  bottom: 0;
  border-radius: 10px;
}
.item-block > .bottom-area > .button > .cover > .check::before {
  width: 3px;
  height: 50%;
}
.item-block > .bottom-area > .button > .cover > .check::after {
  width: 100%;
  height: 3px;
}
.cart-items {
  position: relative;
}
.no-content {
  position: relative;
}
.no-content > .text {
  font-size: 14px;
}
.cart-item {
  display: flex;
  padding: 20px 0;
}
.cart-item > .right > .name {
  font-size: 14px;
  font-weight: bold;
  line-height: 1.5;
  margin-bottom: 10px;
}
.cart-item > .right > .price {
  font-size: 20px;
  font-weight: bold;
  margin-bottom: 16px;
}
.cart-item > .right > .count {
  display: flex;
  align-items: center;
}
.cart-item > .right > .count > .number {
  font-size: 14px;
  margin: 0 14px;
  width: 20px;
  text-align: center;
}
.cart-item > .right > .count .button {
  cursor: pointer;
  width: 28px;
  height: 28px;
  border-radius: 100%;
  background-color: #eee;
  font-size: 16px;
  font-weight: bold;
  display: flex;
  justify-content: center;
  align-items: center;
  transition: 0.2s;
  user-select: none;
}
.cart-item > .right > .count .button:hover {
  background-color: #ddd;
}
.cart-image {
  width: 90px;
  height: 90px;
  border-radius: 100%;
  background-color: #eee;
  overflow: hidden;
  align-items: center;
  justify-content: center;
  margin-right: 34px;
}
.cart-image > .image-wrapper > .image {
  display: block;
  width: 100%;
}
.buttonText-leave-active, .buttonText-enter-active {
  transition: opacity 0.2s, top 0.35s;
}
.buttonText-leave-to, .buttonText-enter {
  opacity: 0;
}
.cartList-enter-active {
  transition: all 2s;
}
.cartList-enter-active > .right > .name, .cartList-enter-active > .right > .price {
  transition: 0.4s;
}
.cartList-enter-active > .right > .name {
  transition-delay: 0.7s;
}
.cartList-enter-active > .right > .price {
  transition-delay: 0.85s;
}
.cartList-enter-active > .right > .count {
  transition: opacity 0.4s;
  transition-delay: 1s;
}
.cartList-enter-active .cart-image {
  transition: 0.5s cubic-bezier(0.79, 0.01, 0.22, 1);
}
.cartList-enter-active .cart-image > .image-wrapper {
  transition: 0.5s cubic-bezier(0.79, 0.01, 0.22, 1) 0.1s;
}
.cartList-enter > .right > .name, .cartList-enter > .right > .price {
  opacity: 0;
  transform: translateX(30px);
}
.cartList-enter > .right .count {
  opacity: 0;
}
.cartList-enter .cart-image {
  transform: scale(0);
}
.cartList-enter .cart-image > .image-wrapper {
  transform: scale(0);
}
.cartList-leave-active {
  transition: 0.7s cubic-bezier(0.79, 0.01, 0.22, 1);
  position: absolute;
}
.cartList-leave-to {
  transform: scale(0);
  opacity: 0;
}
.cartList-move {
  transition: 0.7s cubic-bezier(0.79, 0.01, 0.22, 1);
}
.noContent-enter-active, .noContent-leave-active {
  transition: opacity 0.5s;
  position: absolute;
}
.noContent-enter, .noContent-leave-to {
  opacity: 0;
}
.checkout-button {
    cursor: pointer;
    background-color: #f6c90e;
    font-weight: bold;
    font-size: 14px;
    box-sizing: border-box;
    height: 46px;
    padding: 16px 20px;
    border-radius: 100px;
    box-shadow: 0 3px 6px rgba(0, 0, 0, 0.2);
    transition: box-shadow 0.4s, background-color 0.2s;
    user-select: none;
    white-space: nowrap;
    position: relative;
    display: flex;
    align-items: center;
    justify-content: center;
    overflow: hidden;
    width: 40%;
  }
  #checkoutForm{
    display: none;
  }
</style>
)=====";

const static char index_third[] PROGMEM = R"=====(
<script>
    function showCart(){
        console.log("showCart() function is called.");
        $("#shopItems").hide();
        $("#cartItems").show();
       
    }
    function hideCart(){
        $("#cartItems").hide();
        $("#shopItems").show();
        
    }
    
    document.addEventListener('DOMContentLoaded', function() {
    const shopItemsContainer = document.querySelector('.shop-items');
    const cartItemsContainer = document.querySelector('.cart-items');

    const app = {
        shopItems: [],
        cartItems: [],

        increment(cartItem) {
            cartItem.count++;
            this.renderCartItems();
        },
    
        decrement(cartItem) {
            if (cartItem.count > 1) {
                cartItem.count--;
            } else {
                const itemIndex = this.cartItems.findIndex(item => item.id === cartItem.id);
                if (itemIndex !== -1) {
                    this.cartItems.splice(itemIndex, 1);
                    this.updateCheckoutButton();
                    this.fetchShopItems();
                }
            }
            this.renderCartItems();
            
        },
        checkout() {
            const referrer = window.location.href;
            const url = new URL(referrer);
            const referrerParams = url.search;
            console.log(referrerParams);
            
            this.cartItems.forEach(item => {
                console.log(`${item.name} - Count: ${item.count}`);
            });

            
            if (this.cartItems.length > 0) {
                const cartItemParams = this.cartItems.map(item => `${item.name}:${item.count}`).join(',')+referrerParams+';';
                console.log(cartItemParams);

                const cartItemsInput = document.getElementById('cartItemsInput');
                cartItemsInput.value = cartItemParams;

                // Trigger form submission
                const checkoutForm = document.getElementById('checkoutForm');
                checkoutForm.submit();
            }
        },

        init() {
            this.fetchShopItems();
            this.attachEventListeners();
        },

        fetchShopItems() {
            fetch("https://raw.githubusercontent.com/ShebinJoseJacob/SQ/main/list.json")
                .then(response => response.json())
                .then(data => {
                    this.shopItems = data.items;
                    this.renderShopItems();
                })
                .catch(error => {
                    console.error("Error fetching shop items:", error);
                });
        },

        renderShopItems() {
            shopItemsContainer.innerHTML = '';

            this.shopItems.forEach(item => {
                if (typeof item.inCart === 'undefined') {
                    item.inCart = false;
                }
                const itemElement = this.createShopItemElement(item);
                shopItemsContainer.appendChild(itemElement);
            });
        },

        createShopItemElement(item) {
            const itemDiv = document.createElement('div');
            itemDiv.className = 'item';
        
            const itemBlockDiv = document.createElement('div');
            itemBlockDiv.className = 'item-block';
        
            const imageAreaDiv = document.createElement('div');
            imageAreaDiv.className = 'image-area';
            imageAreaDiv.style.backgroundColor = item.color;
        
            const image = document.createElement('img');
            image.className = 'image';
            image.src = item.image;
            imageAreaDiv.appendChild(image);
        
            const nameDiv = document.createElement('div');
            nameDiv.className = 'name';
            nameDiv.textContent = item.name;
        
            const descriptionDiv = document.createElement('div');
            descriptionDiv.className = 'description';
            descriptionDiv.textContent = item.description;
        
            const bottomAreaDiv = document.createElement('div');
            bottomAreaDiv.className = 'bottom-area';
        
            const priceDiv = document.createElement('div');
            priceDiv.className = 'price';
            priceDiv.textContent = `$${item.price}`;
            bottomAreaDiv.appendChild(priceDiv);
        
            const buttonDiv = document.createElement('div');
            buttonDiv.className = 'button';
            buttonDiv.dataset.itemId = item.id;
            buttonDiv.textContent = 'ADD TO CART';
            bottomAreaDiv.appendChild(buttonDiv);
        
            itemBlockDiv.appendChild(imageAreaDiv);
            itemBlockDiv.appendChild(nameDiv);
            itemBlockDiv.appendChild(descriptionDiv);
            itemBlockDiv.appendChild(bottomAreaDiv);
            itemDiv.appendChild(itemBlockDiv);
        
            return itemDiv;
        },
        
)=====";

const static char index_fourth[] PROGMEM = R"=====(
        addToCart(itemId) {
            const selectedItem = this.shopItems.find(item => item.id === parseInt(itemId));
            if (selectedItem && !selectedItem.inCart) {
                selectedItem.inCart = true;
                const newItem = { ...selectedItem, count: 1 };
                this.cartItems.push(newItem);

                const animationTarget = document.querySelector(`.button[data-item-id="${itemId}"]`);
                animationTarget.textContent = '✓';
                animationTarget.style.pointerEvents = 'none';
                gsap.to(animationTarget, {
                    width: 46,
                    duration: 0.8,
                    ease: "power4"
                  });
                // Use your GSAP animation here
                this.renderCartItems();
                this.updateCheckoutButton();
            }
            setTimeout(() => {
                cartItemsContainer.scrollTop = cartItemsContainer.scrollHeight;
            });
        },
        renderCartItems() {
            cartItemsContainer.innerHTML = '';
            this.cartItems.forEach(cartItem => {
                const cartItemElement = this.createCartItemElement(cartItem);
                cartItemsContainer.appendChild(cartItemElement);
            });

            if (this.cartItems.length === 0) {
                const noContentElement = document.createElement('div');
                noContentElement.className = 'no-content';
                noContentElement.innerHTML = '<p class="text">Your cart is empty.</p>';
                cartItemsContainer.appendChild(noContentElement);
            }
            else{
                this.createCheckoutButton();
            }
            
        },
        
)=====";

const static char index_fifth[] PROGMEM = R"=====(
        updateCheckoutButton() {
            const checkoutButtonContainer = document.getElementById('checkoutButtonContainer');
            if (this.cartItems.length > 0) {
                checkoutButtonContainer.style.display = 'block';
            } else {
                checkoutButtonContainer.style.display = 'none';
            }
        },

        createCartItemElement(cartItem) {
            const cartItemDiv = document.createElement('div');
            cartItemDiv.className = 'cart-item';

            const leftDiv = document.createElement('div');
            leftDiv.className = 'left';

            const cartImageDiv = document.createElement('div');
            cartImageDiv.className = 'cart-image';

            const imageWrapperDiv = document.createElement('div');
            imageWrapperDiv.className = 'image-wrapper';

            const image = document.createElement('img');
            image.className = 'image';
            image.src = cartItem.image;
            imageWrapperDiv.appendChild(image);

            cartImageDiv.appendChild(imageWrapperDiv);
            leftDiv.appendChild(cartImageDiv);

            const rightDiv = document.createElement('div');
            rightDiv.className = 'right';

            const nameDiv = document.createElement('div');
            nameDiv.className = 'name';
            nameDiv.textContent = cartItem.name;

            const priceDiv = document.createElement('div');
            priceDiv.className = 'price';
            priceDiv.textContent = `$${cartItem.price.toFixed(2)}`;

            const countDiv = document.createElement('div');
            countDiv.className = 'count';

            const decrementButton = document.createElement('div');
            decrementButton.className = 'button';
            decrementButton.textContent = '<';
            decrementButton.addEventListener('click', () => this.decrement(cartItem));

            const numberDiv = document.createElement('div');
            numberDiv.className = 'number';
            numberDiv.textContent = cartItem.count;

            const incrementButton = document.createElement('div');
            incrementButton.className = 'button';
            incrementButton.textContent = '>';
            incrementButton.addEventListener('click', () => this.increment(cartItem));

            countDiv.appendChild(decrementButton);
            countDiv.appendChild(numberDiv);
            countDiv.appendChild(incrementButton);

            rightDiv.appendChild(nameDiv);
            rightDiv.appendChild(priceDiv);
            rightDiv.appendChild(countDiv);

            cartItemDiv.appendChild(leftDiv);
            cartItemDiv.appendChild(rightDiv);

            return cartItemDiv;
        },
)=====";

const static char index_sixth[] PROGMEM = R"=====(
        createCheckoutButton() {
            const checkoutButtonContainer = document.getElementById('checkoutButtonContainer');
            
            const existingCheckoutButton = document.querySelector('.checkout-button');
            if (existingCheckoutButton) {
                existingCheckoutButton.remove();
            }
    
            // Create and append the "Checkout" button
            const checkoutButton = document.createElement('div');
            checkoutButton.className = 'checkout-button';
            checkoutButton.textContent = 'Checkout';
            checkoutButton.addEventListener('click', this.checkout.bind(this));
            checkoutButtonContainer.appendChild(checkoutButton);

        },


        attachEventListeners() {
            shopItemsContainer.addEventListener('click', event => {
                if (event.target.classList.contains('button')) {
                    const itemId = event.target.dataset.itemId;
                    this.addToCart(itemId);
                }
            });
        }
    };
    

    app.init();
});

</script>
</body>
</html>
)=====";


const static char res[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Smart Cafe</title>
  <script src="https://cdn.jsdelivr.net/npm/vue@2.6.14/dist/vue.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/axios/0.21.1/axios.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/gsap/3.9.1/gsap.min.js"></script>
  <script src="https://unpkg.com/@lottiefiles/lottie-player@latest/dist/lottie-player.js"></script>
</head>
<body>
  <div class="wrapper">
    <div class="screen -left">
      <div class="app-bar">
        <img class="logo" src="https://s3-us-west-2.amazonaws.com/s.cdpn.io/1315882/pngwave.png" alt="Logo">
      </div>
      <div class="response">
        <lottie-player src="https://lottie.host/22e763a7-13d7-4b7f-8324-4a33b0b5b656/YlSUNUY2fG.json" background="#FFFFFF" speed="1" style="width: 300px; height: 300px; margin-left: -3%;" loop autoplay direction="1" mode="normal"></lottie-player>
    </div>
    <div class="response-text">Your Order Is Getting Ready</div>
    </div>
  </div>
<style>
body {
  font-family: "Rubik", sans-serif;
  color: #303841;
  overflow:hidden ;
}
.wrapper {
  height: 100vh;
  display: flex;
  align-items: center;
  justify-content: space-between;
  position: relative;
  flex-wrap: wrap;
  padding: 40px 20px;
  max-width: 720px;
  margin: 0 auto;
}
.wrapper::before {
  content: "";
  display: block;
  position: fixed;
  width: 300%;
  height: 100%;
  top: 50%;
  left: 50%;
  border-radius: 100%;
  transform: translateX(-50%) skewY(-8deg);
  background-color: #f6c90e;
  z-index: -1;
  animation: wave 8s ease-in-out infinite alternate;
}
@keyframes wave {
  0% {
    transform: translateX(-50%) skew(0deg, -8deg);
  }
  100% {
    transform: translateX(-30%) skew(8deg, -4deg);
  }
}
@media(max-width:700px) {
.screen {
    background-color: #fff;
    box-sizing: border-box;
    width: 340px;
    height: 600px;
    box-shadow: 0 3.2px 2.2px rgba(0, 0, 0, 0.02), 0 7px 5.4px rgba(0, 0, 0, 0.028), 0 12.1px 10.1px rgba(0, 0, 0, 0.035), 0 19.8px 18.1px rgba(0, 0, 0, 0.042), 0 34.7px 33.8px rgba(0, 0, 0, 0.05), 0 81px 81px rgba(0, 0, 0, 0.07);
    border-radius: 30px;
    overflow-y: scroll;
    padding: 0 28px;
    position: relative;
    margin-bottom: 20px;
    margin-left: 10%;
    }
    .response{
        height: 300px;
        width: 300px;
        align-items: center;
    }
}
@media (min-width: 781px) {
    .screen {
    background-color: #fff;
    box-sizing: border-box;
    width: 340px;
    height: 600px;
    box-shadow: 0 3.2px 2.2px rgba(0, 0, 0, 0.02), 0 7px 5.4px rgba(0, 0, 0, 0.028), 0 12.1px 10.1px rgba(0, 0, 0, 0.035), 0 19.8px 18.1px rgba(0, 0, 0, 0.042), 0 34.7px 33.8px rgba(0, 0, 0, 0.05), 0 81px 81px rgba(0, 0, 0, 0.07);
    border-radius: 30px;
    overflow-y: scroll;
    padding: 0 28px;
    position: relative;
    margin-bottom: 20px;
    margin-left: 20%;
    }
}
.screen::before {
  content: "";
  display: block;
  position: absolute;
  width: 300px;
  height: 300px;
  border-radius: 100%;
  background-color: #f6c90e;
  top: -20%;
  left: -50%;
  z-index: 0;
}
.screen::-webkit-scrollbar {
  display: none;
}
.screen > .title {
  font-size: 24px;
  font-weight: bold;
  margin: 20px 0;
  position: relative;
}
.app-bar {
  padding: 12px 0;
  position: relative;
}
.app-bar > .logo {
  display: block;
  width: 50px;
}

.response-text {
    cursor: pointer;
    background-color: #f6c90e;
    font-weight: bold;
    font-size: 14px;
    box-sizing: border-box;
    height: 46px;
    padding: 16px 20px;
    border-radius: 100px;
    box-shadow: 0 3px 6px rgba(0, 0, 0, 0.2);
    transition: box-shadow 0.4s, background-color 0.2s;
    user-select: none;
    white-space: nowrap;
    position: relative;
    display: flex;
    align-items: center;
    justify-content: center;
    overflow: hidden;
    width: 75%;
    margin-left: 13%;
  }
</style>

</body>
</html>
)=====";

const static char admin_first[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Smart Cafe</title>
  <script src="https://cdn.jsdelivr.net/npm/vue@2.6.14/dist/vue.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/axios/0.21.1/axios.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/gsap/3.9.1/gsap.min.js"></script>
  <script type="module" src="https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.esm.js"></script>
  <script nomodule src="https://unpkg.com/ionicons@7.1.0/dist/ionicons/ionicons.js"></script>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.4/jquery.min.js"></script>
<link href="https://fonts.googleapis.com/css2?family=Bebas+Neue&family=Roboto&family=Rubik&family=Lora&display=swap" rel="stylesheet">
</head>
<body>
  <div class="wrapper">
    <div class="screen -left" id="shopItems">
      <div class="app-bar">
      </div>
      <div class="title">Orders</div>
      <div class="shop-items">
        
      </div>
    </div>
  </div>
<style>
body {
  font-family: "Rubik", sans-serif;
  color: #303841;
  overflow: hidden;
}
.wrapper {
  height: 100vh;
  display: flex;
  align-items: center;
  justify-content: space-between;
  position: relative;
  flex-wrap: wrap;
  padding: 40px 20px;
  max-width: 720px;
  margin: 0 auto;
}
.wrapper::before {
  content: "";
  display: block;
  position: fixed;
  width: 300%;
  height: 100%;
  top: 50%;
  left: 50%;
  border-radius: 100%;
  transform: translateX(-50%) skewY(-8deg);
  background-color: #f6c90e;
  z-index: -1;
  animation: wave 8s ease-in-out infinite alternate;
}
@keyframes wave {
  0% {
    transform: translateX(-50%) skew(0deg, -8deg);
  }
  100% {
    transform: translateX(-30%) skew(8deg, -4deg);
  }
}

@media(max-width:700px) {
.screen {
    background-color: #fff;
    box-sizing: border-box;
    width: 340px;
    height: 600px;
    box-shadow: 0 3.2px 2.2px rgba(0, 0, 0, 0.02), 0 7px 5.4px rgba(0, 0, 0, 0.028), 0 12.1px 10.1px rgba(0, 0, 0, 0.035), 0 19.8px 18.1px rgba(0, 0, 0, 0.042), 0 34.7px 33.8px rgba(0, 0, 0, 0.05), 0 81px 81px rgba(0, 0, 0, 0.07);
    border-radius: 30px;
    overflow-y: scroll;
    padding: 0 28px;
    position: relative;
    margin-bottom: 20px;
    margin-left: 15%;
    }

}
@media (min-width: 781px) {
    .screen {
    background-color: #fff;
    box-sizing: border-box;
    width: 340px;
    height: 600px;
    box-shadow: 0 3.2px 2.2px rgba(0, 0, 0, 0.02), 0 7px 5.4px rgba(0, 0, 0, 0.028), 0 12.1px 10.1px rgba(0, 0, 0, 0.035), 0 19.8px 18.1px rgba(0, 0, 0, 0.042), 0 34.7px 33.8px rgba(0, 0, 0, 0.05), 0 81px 81px rgba(0, 0, 0, 0.07);
    border-radius: 30px;
    overflow-y: scroll;
    padding: 0 28px;
    position: relative;
    margin-bottom: 20px;
    }
}

.screen::before {
  content: "";
  display: block;
  position: absolute;
  width: 300px;
  height: 300px;
  border-radius: 100%;
  background-color: #f6c90e;
  top: -20%;
  left: -50%;
  z-index: 0;
}
.screen::-webkit-scrollbar {
  display: none;
}
.screen > .title {
  font-size: 24px;
  font-weight: bold;
  margin: 20px 0;
  position: relative;
}
.app-bar {
  padding: 12px 0;
  position: relative;
}
.app-bar > .logo {
  display: block;
  width: 50px;
}
.shop-items {
  position: relative;
}
.order-container{
  width: 90%;
  height: auto;
  padding: 1rem;
  margin-bottom: 1rem;
  margin-left: -0.3rem;
  border-radius: 1rem;
  font-family: 'Merriweather', serif;
  display: flex;
  position: relative;
  flex-direction: column;
  box-shadow: 0.3rem 0.3rem 0.6rem #E4EBF5, -0.3rem -0.3rem 10rem #e6eaef94;
}
.table-id{
  font-weight: 600;
  font-size: 1.3rem;
  font-family: 'Bebas Neue', sans-serif;
  padding-bottom: 0.3rem;
}

.item_name{
  padding-bottom: 0.2rem;
  font-size: 0.9rem;
  font-family: 'Lora', serif;
}
</style>
<script>
)=====";

const static char admin_second[] PROGMEM = R"=====(    
document.addEventListener('DOMContentLoaded', function() {
    const shopItemsContainer = document.querySelector('.shop-items');

    const app = {
            shopItems: [],

            init() {
                this.renderShopItems();
                this.attachEventListeners();
            },

            renderShopItems() {
                shopItemsContainer.innerHTML = '';

                for (const tableId in orders) {
                    const items = orders[tableId];

                    // Create a container for each order
                    const orderContainer = document.createElement('div');
                    orderContainer.className = 'order-container';
                    
                    // Create an element to display the table ID
                    const tableIdElement = document.createElement('div');
                    tableIdElement.className = 'table-id';
                    tableIdElement.textContent = `Table ID: ${tableId}`;
                    orderContainer.appendChild(tableIdElement);

                    items.forEach((item, index) => {
                        if (item.name) {
                            const itemElement = this.createShopItemElement(item, index + 1);
                            orderContainer.appendChild(itemElement);
                        }
                    });

                    shopItemsContainer.appendChild(orderContainer);
                }
            },

            createShopItemElement(item, serialNumber) {
                const itemElement = document.createElement('div');
                itemElement.className = 'item';
                const itemName = item.name.replace(/\+/g, ' ');
                itemElement.innerHTML = `<div class="item_name">${serialNumber}. ${itemName} : ${item.count}</div>`;
                return itemElement;
            },
            
            attachEventListeners() {
                shopItemsContainer.addEventListener('dblclick', event => {
                    const tableElement = event.target.closest('.order-container');
                    if (tableElement) {
                        const tableIdElement = tableElement.querySelector('.table-id');
                        if (tableIdElement) {
                            const table_id = tableIdElement.textContent.replace('Table ID: ', '');
                            deleteOrder(table_id);
                            tableElement.remove();
                        }
                    }
                });
            }
        };
    
        function deleteOrder(table_id) {
        const url = "http://192.168.1.7/delete";
        const tableID = table_id + ";";
        const data = new URLSearchParams();
        data.append('table_id', tableID);


        fetch(url, {
            method: 'POST',
            body: data
        })
        .then(response => {
            if (!response.ok) {
              throw new Error(`HTTP error! Status: ${response.status}`);
            }
            // Check if the response body is empty
            if (response.status === 200) {
                return null; // Return null or handle as needed
            }

            return response.json();
        })
        .then(data => {
            console.log('Order deleted:', data);
        })
        .catch(error => {
            console.error('Error deleting order:', error);
        });
    }

    app.init();
});

</script>
</body>
</html>
)=====";
