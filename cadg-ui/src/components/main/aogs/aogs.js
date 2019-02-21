import React, { Component } from 'react';
import {
  Table,
  Container,
  Button,
  Modal,
  ModalHeader,
  ModalBody,
  ModalFooter,
  Row,
  Col
} from 'reactstrap';
import { connect } from 'react-redux';
import AddAOG from './add-aog-modal'

class AOGs extends Component {
  constructor(props) {
    super(props);
    this.state = {
      isAdding: false
    };
    this.toggleAdding = this.toggleAdding.bind(this);
    this.getAOG = this.getAOG.bind(this);
  }

  toggleAdding() {
    this.setState(prevState => ({
      ...prevState,
      isAdding: !prevState.isAdding
    }));
  }

  getAOG() {
    return (
      Object.keys(this.props.aogs).map((id) => {
        return (
          <tr style={{'font-size':'small'}}>
            <th scope='row'>{id}</th>
            <td>{this.props.aogs[id].originator_name}</td>
            <td>{this.props.aogs[id].status}</td>
            <td>{this.props.aogs[id].agency}</td>
          </tr>
        );
      })
    )
  }

  render() {
    return (
      <div>
        <br/><br/><br/><br/>
        <Container >
          <Row>
            <Col>
              <h1>Alert Originator Groups</h1>
            </Col>
            <Col align='right'>
              <Button size='lg' color='primary' onClick={this.toggleAdding}>+</Button>{' '}
            </Col>
          </Row>
          <br/>
          <Table hover responsive size='sm'>
            <thead style={{'font-size':'medium'}}>
            <tr>
              <th>ID#</th>
              <th>Name</th>
              <th>Status</th>
              <th>Agency</th>
            </tr>
            </thead>
            <tbody>
            {this.getAOG()}
            </tbody>
          </Table>
        </Container>
        <AddAOG isAdding={this.state.isAdding} toggle={() => this.toggleAdding()}/>
      </div>
    );
  }
}

const mapStateToProps = state => ({
  aogs: state.aogs.aogs
})


export default connect(mapStateToProps, null)(AOGs);