import 'package:angular2/core.dart';
import 'hero.dart';
import 'hero_detail_component.dart';
final List<Hero> mockHeroes = [
    new Hero(11, 'claude1'),
    new Hero(12, 'claude2'),
    new Hero(13, 'claude3'),
    new Hero(14, 'claude4'),
    new Hero(15, 'claude5'),
    new Hero(16, 'claude6'),
    new Hero(17, 'claude7'),
    new Hero(18, 'claude8'),
    new Hero(19, 'claude9'),
    new Hero(20, 'claude0')
];
@Component(
    selector: 'my-app',
    template: '''
        <h1>{{title}}</h1>
        <h2>My Heros</h2>
        <ul class="heroes" >
            <li *ngFor="let hero of heroes" 
                [class.selected]="hero == selectedHero"
                (click)="onSelect(hero)">
                <span class="badge"> {{hero.id}}</span>{{hero.name}}
            </li>
        </ul>
        <my-hero-detail [hero]="selectedHero"></my-hero-detail>
    ''',
    styles: const [
    '''
        .selected {
            background-color: #CFD8DC !important;
            color: white;
        }
        .heroes {
            margin: 0 0 2em 0;
            list-style-type:none;
            padding: 0;
            width: 10em;
        }
        .heroes li {
            cursor: pointer;
            position: relative;
            left: 0;
            background-color: #EEE;
            margin: .5em;
            padding: .3em 0em;
            height: 1.6em;
            border-radius: 4px;
        }
        .heroes li.selected:hover {
            color: white;
        }
        .heroes li:hover {
            color: #607D8B;
            background-color: #EEE;
            left: .1em;
        }
        .heroes .text {
            position: relative;
            top: -3px;
        }
        .heroes .badge {
            display: inline-block;
            font-size: small;
            color: white;
            padding: 0.8em 0.7em 0 em 0.7em;
            background-color: #607D8B;
            line-hieght: 1em;
            position: relative;
            left: -1px;
            top: -4px;
            height: 1.8em;
            margin-right: .8em;
            border-radius: 4px 0px 0ox 4px;
        }
    '''
    ],
    directives: const [HeroDetailComponent]
)

class AppComponent {
    String title = 'Tour of Heros';
    final List<Hero> heroes = mockHeroes;
    Hero selectedHero;

    onSelect(Hero hero){
        selectedHero = hero;
    }
}

