import Link from "next/link"

export default function AboutPage() {
    return (
        <>
            <header> About Page </header>

                    <nav className = "navbar" >
            <div className = "logo" ><a href="#">Self-Caring Plant</a></div>
                <ul> 
                <li><Link href="/">Home</Link></li>
                <li><Link href="">Camera</Link></li>
                <li><Link href="/about">About</Link></li>
                </ul>
        </nav>


            <div className="content" >
                <div className="aboutSquare" >

                    <h1> Inspiration </h1>
                    <p>
                        My friends and I have a lot of plants,
                        but find we never have time to remember to take care of them :(
                    </p>

                    <h2> What it does </h2>
                    <p>
                        Automatically adjusts the moisture and infrared radiation levels received by the plant by releasing water from a water tank and activating a light as needed.
                        It outputs the statistical information of the health of the plant onto a website along with a time-lapse video of its growth. Our website also allows you to take a snapshot image for yourself whenever you want.
                        Additionally we apply AI models to classNameify the plant leaves' nutrient levels and predict whether there are any imbalances or deficiencies. If there are deficiencies, an action will be suggested to the user on the website and a connected LCD screen.
                    </p>

                    <h3> How we built it </h3>
                    <p>
                        We used a light sensor to determine the amount of light that the plant is receiving.
                        We used a moisture sensor to determine the moisture level of the soil the plant is in right now (assuming soil-based medium).
                        We used a transistor, resistor, tube, and water pump to control the inflow of water. We used HTML and CSS to build our website that is hosted on Github Pages.
                        We also used a database to store information about the moisture and light sensor and easily transmit information from our board and to our webpage.
                        We used esp-idf, arduino, esp32CAM and esp32s boards to make the systems that monitor the plant.
                    </p>

                    <h4> Challenges we ran into </h4>
                    <p>
                        Because we all have different operating systems,
                        finding a database that was compatible for us all was quite difficult.
                        We also ran into a problem of our power supply blowing up and had
                        to figure out alternative methods to powering our system of ESP boards.
                    </p>

                    <h5> Accomplishments that we're proud of </h5>
                    <p>
                        Getting consistent hardware measurements.
                    </p>

                    <h6> What we learned </h6>
                    <p>
                        Resolving conflicts.
                    </p>

                    <h7> What's next for Self Caring Plant </h7>
                    <p>
                        Expand to care for multiple crops at the same time so that it is available for larger scale plant care precision.
                    </p>

                </div>




            </div>
        </>
    );
}