import 'package:angular2/core.dart';
@Component(
    selector: 'my-app',
    template: '''
    <h1>{{title}}</h1>
    <h2>{{hero.name}} details!</h2>
    <div><label>id:</label>{{hero.id}}</div>
    <div>
        <label>name: </label>
        <input [(ngModel)]="hero.name" placeholder="name">
        
    </div>
    '''
    )

class AppComponent {
    String title = 'Tour of Heros';
    Hero hero = new Hero(1, 'windstorm');
}
class Hero {
    final int id;
    String name;

    Hero(this.id, this.name);
}
