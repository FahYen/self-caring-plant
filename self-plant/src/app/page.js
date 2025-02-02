import { getRecords } from "@/server/actions";
import Image from "next/image";
import Link from "next/link"

export default async function Home() {

  const { records } = await getRecords();
  console.log(records);

  return (
    <>
    <nav className = "navbar" >
    <div className = "logo" ><a href="#">Self-Caring Plant</a></div>
        <ul> 
          <li><Link href="/">Home</Link></li>
          <li><Link href="">Camera</Link></li>
          <li><Link href="/about">About</Link></li>
        </ul>
  </nav>


  <div className = "flexbox-container" > 
    
      <p> Ideal Soil Moisture: </p>  
      
      <p> Stage of Plant: </p>
     
      <p> Water frequency: </p>
  
      <p> Lacking Nutrients: </p>
  
      <p> Nutrients being absorbed: </p>
  
     
  </div>
    </>
  );
}
