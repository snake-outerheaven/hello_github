fn main () {


    let x = 5;

    println!("O valor de x no escopo global é {x}");

    let spaces = "string!";

    println!("A string spaces é '{spaces}' e seu tamanho é {}", spaces.len());



    {
        let x = x * 3;

        let spaces = spaces.to_owned() + " Ops";

        println!("O valor de X no escopo interno é {x}");

        println!("O valor de spaces no escopo interno é '{spaces}' e seu tamanho agora é {}", spaces.len());


        {
            let x = x * 2;

            let spaces = "Oi, eu sou um Rustáceo!";

            println!("O valor de X no escopo mais interno é {x}");

            println!("O valor de spaces no escopo mais interno é '{spaces}' e seu tamanho é {}", spaces.len());

            

        }
        println!("O valor de x voltou a ser {x}, pois o programa saiu do escopo mais interno.");
    }

    println!("O valor de x voltou a ser {x}. pois voltamos ao escopo global.");
}
